#ifndef SERVOS_CONTROLLER_H
#define SERVOS_CONTROLLER_H

#include <ESP32Servo.h>
#include <WebServer.h>

// Pinos Servos
#define SERVO_BASE_PIN 26
#define SERVO_ELEVADOR_PIN 27
#define SERVO_GUINDASTE_PIN 25
#define SERVO_GANCHO_PIN 33

extern Servo servoBase, servoElevador, servoGuindaste, servoGancho;

extern int angleBase, angleElevador, angleGuindaste, angleGancho;
extern int posA[4];
extern int posB[4];

// Funções principais
void iniciarServos();
void moverServo(String servoName, int angle);
void salvarPosicao(String tipo);
void executarMovimento();
void pararMovimento();
void atualizarMovimento();

#endif
