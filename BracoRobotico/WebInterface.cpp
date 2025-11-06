#include "WebInterface.h"
#include "ServosController.h"
#include <Arduino.h>

void iniciarWiFi(const char* ssid, const char* password, IPAddress local_ip, IPAddress gateway, IPAddress subnet) {
  Serial.println("Iniciando Access Point...");
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  Serial.print("Access Point iniciado! IP: ");
  Serial.println(WiFi.softAPIP());
}

//HTML página web
void handleRoot(WebServer &server) {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <meta charset="UTF-8">
      <title>Controle de Servos - ESP32</title>
      <style>
        body { background-color: #121212; color: white; font-family: Arial; text-align: center; }
        h1 { color: #00bfff; }
        input[type=range] { width: 80%%; margin: 15px; }
        .valor { font-size: 20px; margin-bottom: 10px; display: block; }
      </style>
    </head>
    <body>
      <h1>Controle de Servos via Wi-Fi</h1>

      <p>Base: <span id="vBase" class="valor">90</span>°</p>
      <input type="range" min="0" max="180" value="90" oninput="atualizarServo(this.value, 'Base')">

      <p>Elevador: <span id="vElevador" class="valor">25</span>°</p>
      <input type="range" min="0" max="60" value="25" oninput="atualizarServo(this.value, 'Elevador')">

      <p>Guindaste: <span id="vGuindaste" class="valor">145</span>°</p>
      <input type="range" min="110" max="180" value="145" oninput="atualizarServo(this.value, 'Guindaste')">

      <p>Gancho: <span id="vGancho" class="valor">25</span>°</p>
      <input type="range" min="0" max="55" value="25" oninput="atualizarServo(this.value, 'Gancho')">

      <br><br>
      <button onclick="salvar('A')">Salvar A</button>
      <button onclick="salvar('B')">Salvar B</button>
      <button onclick="executar()">Executar</button>
      <button onclick="parar()">Parar</button>

      <script>
        function atualizarServo(valor, nome) {
          document.getElementById('v' + nome).innerText = valor;
          fetch(`/setServo?servo=${nome}&angle=${valor}`);
        }
        function salvar(tipo) { fetch(`/salvar?tipo=${tipo}`).then(r => alert("Posição " + tipo + " salva!")); }
        function executar() { fetch(`/executar`).then(r => alert("Executando movimento de A → B")); }
        function parar() { fetch(`/parar`).then(r => alert("Parando movimento...")); }
      </script>
    </body>
    </html>
  )rawliteral";
  server.send(200, "text/html", html);
}

void configurarRotas(WebServer &server) {
  server.on("/", [&]() { handleRoot(server); });

  server.on("/setServo", [&]() {
    if (server.hasArg("servo") && server.hasArg("angle")) {
      moverServo(server.arg("servo"), server.arg("angle").toInt());
      server.send(200, "text/plain", "OK");
    } else {
      server.send(400, "text/plain", "Parâmetros ausentes");
    }
  });

  server.on("/salvar", [&]() {
    if (server.hasArg("tipo")) {
      salvarPosicao(server.arg("tipo"));
      server.send(200, "text/plain", "OK");
    } else {
      server.send(400, "text/plain", "Tipo ausente");
    }
  });

  server.on("/executar", [&]() {
    server.send(200, "text/plain", "Executando...");
    executarMovimento();
  });

  server.on("/parar", [&]() {
    pararMovimento();
    server.send(200, "text/plain", "OK");
  });
}
