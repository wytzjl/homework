// ex03.ino 修复版 SOS摩斯码 非阻塞millis实现
const int ledPin = 2;

// 摩斯码标准时间参数(ms)
const int DOT_ON  = 200;    // 短亮
const int DASH_ON = 600;    // 长亮
const int SYM_GAP = 200;    // 单个点/划之间熄灭间隔
const int CHAR_GAP = 500;   // 字母之间间隔(S-O、O-S)
const int WORD_GAP = 2000;  // 完整SOS一轮后的长停顿

// 设备状态
enum LedState {
  IDLE,       // 熄灭等待
  DOT_LIGHT,  // 短亮阶段
  DASH_LIGHT, // 长亮阶段
  SYM_WAIT,   // 符号熄灭间隔
  CHAR_WAIT,  // 字母熄灭间隔
  WORD_WAIT   // 一轮SOS结束长等待
};
LedState curState = WORD_WAIT;

// SOS序列定义：0=短点，1=长划
int sosSeq[] = {0,0,0, 1,1,1, 0,0,0};
int seqIndex = 0; // 当前执行到序列第几位
unsigned long timeStamp = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  unsigned long now = millis();
  unsigned long delta = now - timeStamp;

  switch(curState)
  {
    case WORD_WAIT:
      digitalWrite(ledPin, LOW);
      if(delta >= WORD_GAP){
        seqIndex = 0;
        timeStamp = now;
        // 第一个符号：短点
        curState = DOT_LIGHT;
      }
      break;

    case DOT_LIGHT:
      digitalWrite(ledPin, HIGH);
      if(delta >= DOT_ON){
        digitalWrite(ledPin, LOW);
        timeStamp = now;
        curState = SYM_WAIT;
      }
      break;

    case DASH_LIGHT:
      digitalWrite(ledPin, HIGH);
      if(delta >= DASH_ON){
        digitalWrite(ledPin, LOW);
        timeStamp = now;
        curState = SYM_WAIT;
      }
      break;

    case SYM_WAIT:
      if(delta >= SYM_GAP){
        seqIndex++;
        timeStamp = now;
        // 判断是否切换字母
        if(seqIndex == 3 || seqIndex == 6){
          curState = CHAR_WAIT;
        }else if(seqIndex >= 9){
          // 整套SOS播放完成，进入长等待
          curState = WORD_WAIT;
        }else{
          // 下一个符号：短/长
          if(sosSeq[seqIndex] == 0) curState = DOT_LIGHT;
          else curState = DASH_LIGHT;
        }
      }
      break;

    case CHAR_WAIT:
      if(delta >= CHAR_GAP){
        timeStamp = now;
        if(sosSeq[seqIndex] == 0) curState = DOT_LIGHT;
        else curState = DASH_LIGHT;
      }
      break;
  }
}