// ex02.ino
// 1Hz LED闪烁，使用 millis() 无阻塞

const int ledPin = 2;
unsigned long previousMillis = 0;
const long interval = 1000; // 1000ms = 1Hz
int ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}