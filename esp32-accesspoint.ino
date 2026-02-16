#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32-Test-AP";
const char* password = "12345678";

WebServer server(80);

const int ledPin = 2;
bool ledState = false;

String getHTML() {
  String html = "<!DOCTYPE html><html>";
  html += "<head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>";
  html += "body{font-family:Arial;text-align:center;background:#f2f2f2;}";
  html += "button{padding:15px 30px;font-size:18px;margin:10px;border:none;border-radius:8px;}";
  html += ".on{background-color:green;color:white;}";
  html += ".off{background-color:red;color:white;}";
  html += "</style>";
  html += "</head><body>";
  html += "<h1>ESP32 Test Arayuzu</h1>";
  html += "<p>Access Point basariyla calisiyor.</p>";
  
  if (ledState)
    html += "<p>LED Durumu: ACIK</p><a href='/off'><button class='off'>LED KAPAT</button></a>";
  else
    html += "<p>LED Durumu: KAPALI</p><a href='/on'><button class='on'>LED AC</button></a>";

  html += "</body></html>";
  return html;
}

void handleRoot() {
  server.send(200, "text/html", getHTML());
}

void handleOn() {
  ledState = true;
  digitalWrite(ledPin, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  ledState = false;
  digitalWrite(ledPin, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.softAP(ssid, password);

  Serial.println("Access Point Baslatildi");
  Serial.print("IP Adresi: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
}

void loop() {
  server.handleClient();
}
