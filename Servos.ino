#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

// --- Configuração Wi-Fi (Access Point) ---
const char* ssid = "ESP32_BRACO_ROBOTICO";
const char* password = "12345678";

IPAddress local_ip(192, 168, 15, 5);
IPAddress gateway(192, 168, 15, 5);
IPAddress subnet(255, 255, 255, 0);
 
// --- Servos ---
#define SERVO_BASE_PIN 26 // min 0 max 180 
#define SERVO_ELEVADOR_PIN 27 // min 0 max 50
#define SERVO_GUINDASTE_PIN 25 // min 110 max 180
#define SERVO_GANCHO_PIN 33 // min 0 max 55

Servo servoBase;
Servo servoElevador;
Servo servoGuindaste;
Servo servoGancho;

WebServer server(80);

int angleBase = 90;
int angleElevador = 90;
int angleGuindaste = 90;
int angleGancho = 90;

// --- Página HTML ---
void handleRoot() {
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

      <p>Elevador: <span id="vElevador" class="valor">90</span>°</p>
      <input type="range" min="0" max="60" value="30" oninput="atualizarServo(this.value, 'Elevador')">

      <p>Guindaste: <span id="vGuindaste" class="valor">90</span>°</p>
      <input type="range" min="110" max="180" value="35" oninput="atualizarServo(this.value, 'Guindaste')">

      <p>Gancho: <span id="vGancho" class="valor">90</span>°</p>
      <input type="range" min="0" max="55" value="30" oninput="atualizarServo(this.value, 'Gancho')">

      <script>
        function atualizarServo(valor, nome) {
          document.getElementById('v' + nome).innerText = valor;
          fetch(`/setServo?servo=${nome}&angle=${valor}`);
        }
      </script>
    </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

// --- Função para controlar servos ---
void handleServo() {
  if (server.hasArg("servo") && server.hasArg("angle")) {
    String servoName = server.arg("servo");
    int angle = server.arg("angle").toInt();

    if (servoName == "Base") {
      servoBase.write(angle);
      angleBase = angle;
    } else if (servoName == "Elevador") {
      servoElevador.write(angle);
      angleElevador = angle;
    } else if (servoName == "Guindaste") {
      servoGuindaste.write(angle);
      angleGuindaste = angle;
    } else if (servoName == "Gancho") {
      servoGancho.write(angle);
      angleGancho = angle;
    }

    Serial.printf("Servo %s -> %d°\n", servoName.c_str(), angle);
    server.send(200, "text/plain", "OK");
  } else {
    server.send(400, "text/plain", "Parâmetro ausente");
  }
}

void setup() {
  Serial.begin(115200);

  // --- Inicializa servos ---
  servoBase.attach(SERVO_BASE_PIN);
  servoElevador.attach(SERVO_ELEVADOR_PIN);
  servoGuindaste.attach(SERVO_GUINDASTE_PIN);
  servoGancho.attach(SERVO_GANCHO_PIN);

  servoBase.write(angleBase);
  servoElevador.write(angleElevador);
  servoGuindaste.write(angleGuindaste);
  servoGancho.write(angleGancho);

  // --- Wi-Fi Access Point ---
  Serial.println("Iniciando Access Point...");
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  Serial.print("Access Point iniciado! IP: ");
  Serial.println(WiFi.softAPIP());

  // --- Rotas ---
  server.on("/", handleRoot);
  server.on("/setServo", handleServo);

  server.begin();
  Serial.println("Servidor iniciado!");
}

void loop() {
  server.handleClient();
}
