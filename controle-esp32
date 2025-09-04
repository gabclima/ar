#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <WiFiClient.h>

const char* ssid = "IFPR_IoT";
const char* password = "31mfk76m";
MDNSResponder mdns;
  
ESP8266WebServer server(80);

IRsend irsend(4);  // IR LED no GPIO4 (D2)

// RAW (código para ligara  16°)
uint16_t rawData[] = {
  3132, 1540, 552, 1036, 552, 1036, 552, 300, 516, 300, 520, 300, 520, 1036, 548, 300,
  520, 300, 520, 1036, 548, 1040, 548, 300, 520, 1036, 548, 304, 516, 300, 520, 1036,
  552, 1036, 548, 296, 524, 1036, 548, 1040, 548, 300, 520, 300, 520, 1036, 548, 304,
  516, 300, 520, 300, 520, 1036, 548, 300, 520, 300, 520, 296, 524, 300, 520, 300, 516,
  300, 520, 300, 520, 296, 524, 300, 520, 296, 520, 300, 520, 300, 516, 304, 520, 300,
  516, 300, 520, 300, 520, 296, 524, 300, 520, 300, 516, 300, 520, 1036, 552, 300, 516,
  300, 520, 304, 516, 300, 520, 300, 520, 296, 520, 300, 524, 300, 516, 300, 520, 300,
  520, 296, 548, 272, 524, 300, 516, 300, 520, 300, 516, 300, 520, 304, 520, 300, 516,
  300, 520, 300, 516, 300, 524, 300, 520, 296, 520, 300, 520, 300, 516, 300, 524, 300,
  516, 300, 520, 300, 520, 300, 516, 304, 520, 300, 516, 300, 520, 300, 516, 300, 524,
  300, 520, 300, 516, 300, 520, 300, 520, 300, 520, 300, 520, 296, 520, 300, 524, 296,
  520, 300, 520, 300, 516, 300, 520, 300, 524, 300, 516, 300, 520, 300, 516, 300, 548,
  272, 520, 300, 520, 300, 520, 300, 516, 300, 524, 1036, 544, 300, 524, 1036, 548,
  300, 516, 304, 520, 1036, 552, 1036, 548, 300, 520, 3948, 3136, 1540, 548, 1036, 552,
  1036, 552, 300, 516, 300, 520, 300, 516, 1040, 548, 300, 520, 300, 520, 1036, 548,
  1040, 548, 300, 520, 1036, 548, 300, 520, 300, 520, 1036, 552, 1036, 548, 300, 516,
  1044, 544, 1040, 548, 300, 520, 300, 516, 1040, 548, 300, 520, 300, 520, 1036, 548,
  300, 520, 300, 520, 304, 512, 304, 520, 300, 520, 300, 516, 300, 520, 300, 520, 296,
  524, 300, 520, 300, 516, 300, 520, 300, 516, 300, 524, 300, 520, 300, 516, 300, 520,
  1036, 552, 300, 516, 300, 520, 1036, 552, 300, 516, 300, 520, 1040, 548, 1036, 552,
  300, 516, 300, 520, 300, 516, 300, 520, 304, 520, 300, 516, 300, 520, 300, 520, 300,
  516, 1044, 544, 300, 520, 300, 516, 304, 520, 300, 516, 300, 520, 1036, 552, 300, 516,
  1040, 548, 1040, 548, 1040, 544, 300, 520, 300, 520, 300, 520, 300, 516, 300, 520,
  304, 520, 300, 516, 300, 520, 300, 516, 300, 520, 304, 516, 300, 520, 300, 520, 300,
  516, 300, 524, 300, 516, 300, 520, 300, 516, 300, 520, 300, 524, 300, 516, 300, 520,
  300, 516, 300, 524, 300, 520, 300, 516, 300, 520, 300, 520, 300, 520, 1036, 548, 304,
  516, 300, 520, 300, 516, 1040, 548, 300, 520, 1036, 552, 1036, 552, 300, 516, 300, 520,
  300, 516, 300, 520, 300, 524
};
uint16_t rawLength = sizeof(rawData) / sizeof(rawData[0]);

void handleRoot() {
  server.send(200, "text/html",
              "<html>" \
              "<head><title>ESP8266 IR RAW Demo</title></head>" \
              "<body>" \
              "<h1>Envio de RAW IR pelo ESP8266</h1>" \
              "<p><a href=\"/ir\">Enviar RAW NEC</a></p>" \
              "</body>" \
              "</html>");
}

void handleIr() {
  // Envia o RAW com frequência de 38 kHz
  irsend.sendRaw(rawData, rawLength, 38);
  handleRoot();
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  server.send(404, "text/plain", message);
}

void setup(void) {
  irsend.begin();

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado em ");
  Serial.println(ssid);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS iniciado");
  }

  server.on("/", handleRoot);
  server.on("/ir", handleIr);
  server.on("/inline", [](){
    server.send(200, "text/plain", "Funciona também");
  });
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop(void) {
  server.handleClient();
}
