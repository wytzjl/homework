#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "Pura 70";
const char* password = "sxj123456";

WebServer server(80);

#define TOUCH_PIN 4
#define LED_PIN   2

bool armed = false;
bool isAlarm = false; // 改名解决alarm关键字冲突
unsigned long lastFlash = 0;

void handleRoot() {
  String html = "<h1>ESP32 安防报警器</h1>";
  html += "<p>状态: " + String(armed ? "已布防" : "已撤防") + "</p>";
  html += "<p>报警: " + String(isAlarm ? "触发" : "正常") + "</p>";
  html += "<p><a href='/arm'>布防</a> <a href='/disarm'>撤防</a></p>";
  server.send(200, "text/html", html);
}

void handleArm() {
  armed = true;
  isAlarm = false;
  digitalWrite(LED_PIN, LOW);
  // 页面跳转替代redirect
  server.send(302, "text/plain", "Location: /");
}

void handleDisarm() {
  armed = false;
  isAlarm = false;
  digitalWrite(LED_PIN, LOW);
  // 页面跳转替代redirect
  server.send(302, "text/plain", "Location: /");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("正在连接WiFi ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi连接成功，访问地址：http://" + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/arm", handleArm);
  server.on("/disarm", handleDisarm);
  server.begin();
}

void loop() {
  server.handleClient();

  if (armed && !isAlarm) {
    int val = touchRead(TOUCH_PIN);
    if (val < 25) isAlarm = true;
  }

  if (isAlarm) {
    if (millis() - lastFlash > 100) {
      lastFlash = millis();
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }
  }
}