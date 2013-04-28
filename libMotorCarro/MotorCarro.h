/*
*
* MotorCarro
* Biblioteca para mover um carro com dois motores e driver baseado no L298N
*
*/

#ifndef MotorCarro_h
#define MotorCarro_h

#include "Arduino.h"

class MotorCarro {
	public:
		MotorCarro(int pinoENA, int pinoIN1, int pinoIN2,
			int pinoENB, int pinoIN3, int pinoIN4);
		void paraFrente();
		void paraTras();
		void parado();
		void paraDireitaFrente();
		void paraEsquerdaFrente();
		void giraDireita();
		void giraEsquerda();
		void paraDireitaTras();
		void paraEsquerdaTras();
		void serialPrint(int serialPrint);
		
	private:
                void motorParaTras(int motor);
                void motorParaFrente(int motor);
                void motorParado(int motor);
		int _pinoENA;
		int _pinoIN1;
		int _pinoIN2;
		int _pinoENB;
		int _pinoIN3;
		int _pinoIN4;
		int _serialPrint;
};

#endif
