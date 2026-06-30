#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "wyt";
const char* password = "wytzjl445220";

WebServer server(80);

#define LED_PIN 2
const int pwmFreq = 5000;
const int pwmRes = 8;

void handleRoot() {
  String html = "<!DOCTYPE html>";
  html += "<h1>ESP32 Web 无极调光</h1>";
  html += "<input type='range' min='0' max='255' id='slider'>";
  html += "<p>亮度: <span id='val'>0</span></p>";
  html += "<script>";
  html += "let s=document.getElementById('slider');";
  html += "let v=document.getElementById('val');";
  html += "s.oninput=function(){let val=s.value;v.textContent=val;fetch('/set?d='+val);}";
  html += "</script>";
  server.send(200, "text/html", html);
}

void handleSet() {
  if (server.hasArg("d")) {
    int duty = server.arg("d").toInt();
    duty = constrain(duty, 0, 255);
    ledcWrite(LED_PIN, duty);
    Serial.print("当前亮度：");
    Serial.println(duty);
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  // PWM引脚绑定
  ledcAttach(LED_PIN, pwmFreq, pwmRes);
  ledcWrite(LED_PIN, 0);

  // 连接WiFi
  WiFi.begin(ssid, password);
  Serial.print("正在连接WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("设备IP地址：");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/set", handleSet);
  server.begin();
  Serial.println("Web服务已启动");
}

void loop() {
  server.handleClient();
}