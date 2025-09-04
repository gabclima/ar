#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <IRremote.h>   // Biblioteca Arduino-IRremote

const char* ssid = "IFPR_IoT";
const char* password = "31mfk76m";

// WebServer no ESP32
WebServer server(80);

// Pino do LED IR (use GPIO4 ou outro disponível)
const int IR_LED_PIN = 4;
IRsend irsend(IR_LED_PIN);

// RAW fornecido
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
              "<html>"
              "<head><title>ESP32 IR RAW Demo</title></head>"
              "<body>"
              "<h1>Envio de RAW IR pelo ESP32</h1>"
              "<p><a href=\"/ir\">Enviar RAW</a></p>"
              "</body>"
              "</html>");
}

void handleIr() {
  irsend.sendRaw(rawData, rawLength, 38); // 38 kHz
  handleRoot();
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: " + server.uri();
  message += "\nMethod: " + String((server.method() == HTTP_GET) ? "GET" : "POST");
  message += "\nArguments: " + String(server.args()) + "\n";
  for (uint8_t i = 0; i < server.args(); i++)
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  server.send(404, "text/plain", message);
}

void setup() {
  Serial.begin(115200);

  // Inicializa o IR
  IrSender.begin(IR_LED_PIN, true); // true = habilita feedback LED se disponível
  Serial.println("IR Sender iniciado");

  // Conexão Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("\nConectando ao WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS iniciado: http://esp32.local/");
  }

  server.on("/", handleRoot);
  server.on("/ir", handleIr);
  server.on("/inline", []() {
    server.send(200, "text/plain", "Funciona também no ESP32");
  });
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient();
}
