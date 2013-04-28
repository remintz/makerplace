/*
* Teste Motor
*/

#include "MotorCarro.h"

#define PINO_ENA 12
#define PINO_IN1 11
#define PINO_IN2 10
#define PINO_ENB 7
#define PINO_IN3 9
#define PINO_IN4 8

MotorCarro carro(PINO_ENA, PINO_IN1, PINO_IN2, PINO_ENB, PINO_IN3, PINO_IN4);

void setup()
{
  Serial.begin(9600);
}


void loop() {
  carro.paraFrente();
  delay(2000);
  carro.paraDireitaFrente();
  delay(2000);
  carro.paraEsquerdaFrente();
  delay(2000);
  carro.parado();
  delay(2000);
  carro.giraEsquerda();
  delay(2000);
  carro.giraDireita();
  delay(2000);
  carro.parado();
  delay(2000);
  carro.paraDireitaTras();
  delay(2000);
  carro.paraEsquerdaTras();
  delay(2000);
  carro.paraTras();
  delay(2000);
}
