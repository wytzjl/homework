// lab03.ino
// ESP32 呼吸灯实验（PWM）

const int ledPin = 2;
const int freq = 5000;
const int resolution = 8;

void setup() {
  Serial.begin(115200);
  ledcAttach(ledPin, freq, resolution);
}

void loop() {
  // 逐渐变亮
  for (int duty = 0; duty <= 255; duty++) {
    ledcWrite(ledPin, duty);
    delay(10);
  }
  // 逐渐变暗
  for (int duty = 255; duty >= 0; duty--) {
    ledcWrite(ledPin, duty);
    delay(10);
  }
  Serial.println("Breath cycle done");
}