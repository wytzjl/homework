// ex06 警车双闪 双通道反向PWM
#define LED1_PIN 2
#define LED2_PIN 17

const int freq = 5000;
const int resolution = 8;

void setup() {
  Serial.begin(115200);
  ledcAttach(LED1_PIN, freq, resolution);
  ledcAttach(LED2_PIN, freq, resolution);
}

void loop() {
  // A渐亮 B渐暗
  for (int d = 0; d <= 255; d++) {
    ledcWrite(LED1_PIN, d);
    ledcWrite(LED2_PIN, 255 - d);
    delay(8);
  }
  // A渐暗 B渐亮
  for (int d = 255; d >= 0; d--) {
    ledcWrite(LED1_PIN, d);
    ledcWrite(LED2_PIN, 255 - d);
    delay(8);
  }
}