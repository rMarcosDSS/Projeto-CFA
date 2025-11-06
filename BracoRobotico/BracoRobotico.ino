#include <WiFi.h>
#include <WebServer.h>
#include "ServosController.h"
#include "WebInterface.h"

// Configuração Wi-Fi (Access Point) HTTP
const char* ssid = "ESP32_BRACO_ROBOTICO";
const char* password = "12345678";

IPAddress local_ip(192, 168, 15, 5);
IPAddress gateway(192, 168, 15, 5);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Inicializa módulos
  iniciarServos();
  iniciarWiFi(ssid, password, local_ip, gateway, subnet);

  // Configura rotas da interface web
  configurarRotas(server);

  server.begin();
  Serial.println("Servidor iniciado!");
}

void loop() {
  server.handleClient();
  atualizarMovimento();  // Atualiza o movimento do braço robótico
}
