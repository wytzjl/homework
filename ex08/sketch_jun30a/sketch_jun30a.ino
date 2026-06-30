#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "Pura 70";
const char* password = "sxj1232456";

WebServer server(80);

#define TOUCH_PIN 4

void handleRoot() {
  String html = "<!DOCTYPE html>";
  html += "<h1>实时触摸传感器仪表盘</h1>";
  html += "<h1 style='font-size:48px' id='val'>0</h1>";
  html += "<script>";
  html += "setInterval(()=>fetch('/data').then(r=>r.text()).then(v=>{";
  html += "document.getElementById('val').textContent=v;}),100);";
  html += "</script>";
  server.send(200, "text/html", html);
}

void handleData() {
  int val = touchRead(TOUCH_PIN);
  server.send(200, "text/plain", String(val));
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
}

void loop() {
  server.handleClient();
}