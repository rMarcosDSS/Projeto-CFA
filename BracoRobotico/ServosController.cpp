#include "ServosController.h"
#include <Arduino.h>

Servo servoBase, servoElevador, servoGuindaste, servoGancho;

// Ângulos iniciais
int angleBase = 90;
int angleElevador = 25;
int angleGuindaste = 145;
int angleGancho = 25;

// Variáveis para controle do movimento
static bool executando = false;
static unsigned long ultimoMovimento = 0;
static int etapaAtual = 0;
static bool movimentoParaA = true;

// Posições A e B
int posA[4] = {90, 25, 145, 25};
int posB[4] = {90, 25, 145, 25};

void iniciarServos() {
  servoBase.attach(SERVO_BASE_PIN, 500, 2400);
  servoElevador.attach(SERVO_ELEVADOR_PIN, 500, 2400);
  servoGuindaste.attach(SERVO_GUINDASTE_PIN, 500, 2400);
  servoGancho.attach(SERVO_GANCHO_PIN, 500, 2400);

  servoBase.write(angleBase);
  servoElevador.write(angleElevador);
  servoGuindaste.write(angleGuindaste);
  servoGancho.write(angleGancho);

  Serial.println("Servos inicializados.");
}

void moverServo(String servoName, int angle) {
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
}

void salvarPosicao(String tipo) {
  int* destino = (tipo == "A") ? posA : posB;

  destino[0] = angleBase;
  destino[1] = angleElevador;
  destino[2] = angleGuindaste;
  destino[3] = angleGancho;

  Serial.printf("Posição %s salva!\n", tipo.c_str());
}

void executarMovimento() {
  Serial.println("Executando movimento A → B...");
  executando = true;
  etapaAtual = 0;
  movimentoParaA = true;
  ultimoMovimento = millis();
}

void pararMovimento() {
  Serial.println("Parando movimento...");
  executando = false;
}

// Função para ser chamada no loop principal do Arduino
void atualizarMovimento() {
  if (!executando) return;

  unsigned long tempoAtual = millis();
  int* posAtual = movimentoParaA ? posA : posB;
  
  // Verifica se passou tempo suficiente desde o último movimento
  if (tempoAtual - ultimoMovimento >= (etapaAtual == 3 ? 1000 : 500)) {
    switch (etapaAtual) {
      case 0:
        servoBase.write(posAtual[0]);
        break;
      case 1:
        servoGuindaste.write(posAtual[2]);
        break;
      case 2:
        servoElevador.write(posAtual[1]);
        break;
      case 3:
        servoGancho.write(posAtual[3]);
        break;
    }
    
    etapaAtual++;
    if (etapaAtual > 3) {
      etapaAtual = 0;
      movimentoParaA = !movimentoParaA;
    }
    
    ultimoMovimento = tempoAtual;
  }
}
