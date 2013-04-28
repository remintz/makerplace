/*
* Teste Motor
*/

#include "Arduino.h"
#include "MotorCarro.h"

#define MOTOR_A 1
#define MOTOR_B 2

MotorCarro::MotorCarro(int pinoENA, int pinoIN1, int pinoIN2,
			int pinoENB, int pinoIN3, int pinoIN4) {
	_pinoENA = pinoENA;
	_pinoIN1 = pinoIN1;
	_pinoIN2 = pinoIN2;
	_pinoENB = pinoENB;
	_pinoIN3 = pinoIN3;
	_pinoIN4 = pinoIN4;
	pinMode(_pinoENA, OUTPUT);
	pinMode(_pinoIN1, OUTPUT);
	pinMode(_pinoIN2, OUTPUT);
	pinMode(_pinoENB, OUTPUT);
	pinMode(_pinoIN3, OUTPUT);
	pinMode(_pinoIN4, OUTPUT);
	_serialPrint = 0;
}

void MotorCarro::motorParaTras(int motor) {
  if (motor == MOTOR_A) {
    digitalWrite(_pinoENA, HIGH);
    digitalWrite(_pinoIN2, HIGH);
    digitalWrite(_pinoIN1, LOW);
  } else {
    digitalWrite(_pinoENB, HIGH);
    digitalWrite(_pinoIN4, HIGH);
    digitalWrite(_pinoIN3, LOW);
  }
}

void MotorCarro::motorParaFrente(int motor) {
  if (motor == MOTOR_A) {
    digitalWrite(_pinoENA, HIGH);
    digitalWrite(_pinoIN2, LOW);
    digitalWrite(_pinoIN1, HIGH);
  } else {
    digitalWrite(_pinoENB, HIGH);
    digitalWrite(_pinoIN4, LOW);
    digitalWrite(_pinoIN3, HIGH);
  }
}

void MotorCarro::motorParado(int motor) {
  if (motor == MOTOR_A) {
    digitalWrite(_pinoENA, LOW);
    digitalWrite(_pinoIN2, LOW);
    digitalWrite(_pinoIN1, LOW);
  } else {
    digitalWrite(_pinoENB, LOW);
    digitalWrite(_pinoIN4, LOW);
    digitalWrite(_pinoIN3, LOW);
  }
}

void MotorCarro::paraFrente() {
  if (_serialPrint)
    Serial.println("carroParaFrente");
  motorParaFrente(MOTOR_A);
  motorParaFrente(MOTOR_B);
}

void MotorCarro::paraTras() {
  if (_serialPrint)
    Serial.println("carroParaTras");
  motorParaTras(MOTOR_A);
  motorParaTras(MOTOR_B);
}

void MotorCarro::parado() {
  if (_serialPrint)
    Serial.println("carroParado");
  motorParado(MOTOR_A);
  motorParado(MOTOR_B);
}

void MotorCarro::paraDireitaFrente() {
  if (_serialPrint)
    Serial.println("carroParaDireitaFrente");
  motorParaFrente(MOTOR_A);
  motorParado(MOTOR_B);
}

void MotorCarro::paraEsquerdaFrente() {
  if (_serialPrint)
    Serial.println("carroParaEsquerdaFrente");
  motorParado(MOTOR_A);
  motorParaFrente(MOTOR_B);
}

void MotorCarro::giraDireita() {
  if (_serialPrint)
    Serial.println("carroGiraDireita");
  motorParaFrente(MOTOR_A);
  motorParaTras(MOTOR_B);
}

void MotorCarro::giraEsquerda() {
  if (_serialPrint)
    Serial.println("carroGiraEsquerda");
  motorParaTras(MOTOR_A);
  motorParaFrente(MOTOR_B);
}

void MotorCarro::paraDireitaTras() {
  if (_serialPrint)
    Serial.println("carroParaDireitaTras");
  motorParado(MOTOR_A);
  motorParaTras(MOTOR_B);
}

void MotorCarro::paraEsquerdaTras() {
  if (_serialPrint)
    Serial.println("carroParaEsquerdaTras");
  motorParaTras(MOTOR_A);
  motorParado(MOTOR_B);
}

void MotorCarro::serialPrint(int serialPrint) {
  _serialPrint = serialPrint;
}
