// ex03.ino
// SOS 求救信号（摩斯码），使用 millis() 实现

const int ledPin = 2;
unsigned long prevMs = 0;

// 摩斯码时间（单位：ms）
const int dot = 200;     // 短亮
const int dash = 600;    // 长亮
const int gap = 200;     // 符号间隔
const int charGap = 500; // 字母间隔
const int wordGap = 2000;// 完整SOS后停顿

// 状态机定义
enum State {
  S1_DOT1, S1_DOT2, S1_DOT3,
  O1_DASH1, O1_DASH2, O1_DASH3,
  S2_DOT1, S2_DOT2, S2_DOT3,
  WAIT
};

State state = S1_DOT1;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long now = millis();

  switch (state) {
    // S: ...
    case S1_DOT1: doDot(now, S1_DOT2); break;
    case S1_DOT2: doDot(now, S1_DOT3); break;
    case S1_DOT3: doDot(now, O1_DASH1); break;

    // O: ---
    case O1_DASH1: doDash(now, O1_DASH2); break;
    case O1_DASH2: doDash(now, O1_DASH3); break;
    case O1_DASH3: doDash(now, S2_DOT1); break;

    // S: ...
    case S2_DOT1: doDot(now, S2_DOT2); break;
    case S2_DOT2: doDot(now, S2_DOT3); break;
    case S2_DOT3: doDot(now, WAIT); break;

    // 停顿后重新开始
    case WAIT:
      digitalWrite(ledPin, LOW);
      if (now - prevMs >= wordGap) {
        state = S1_DOT1;
        prevMs = now;
      }
      break;
  }
}

// 短亮
void doDot(unsigned long now, State next) {
  digitalWrite(ledPin, HIGH);
  if (now - prevMs >= dot) {
    digitalWrite(ledPin, LOW);
    prevMs = now;
    state = next;
  }
}

// 长亮
void doDash(unsigned long now, State next) {
  digitalWrite(ledPin, HIGH);
  if (now - prevMs >= dash) {
    digitalWrite(ledPin, LOW);
    prevMs = now;
    state = next;
  }
}