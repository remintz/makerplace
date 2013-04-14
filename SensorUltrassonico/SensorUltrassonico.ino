/*
  Exemplo de utilizacao do sensor ultrassonico HC-SR04
  
  Inspirado em http://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/ que, por sua vez
  foi inspirado em  http://goo.gl/kJ8Gl

  Este exemplo acende um led verde se um objeto esta a mais de DISTANCIA_ALARME cm e um led vermelho
  (e toca uma campainha) se o objeto esta a menos de DISTANCIA_ALARME cm
  
  Autor: Renato Mintz
  http://www.makerbh.com.br

*/

int PINO_TRIGGER_SENSOR = 13;
int PINO_ECHO_SENSOR = 12;
int PINO_LED_VERMELHO = 11;
int PINO_LED_VERDE = 10;
int PINO_CAMPAINHA = 9;

int DISTANCIA_ALARME = 10;

void setup() {
  Serial.begin (9600);
  pinMode(PINO_TRIGGER_SENSOR, OUTPUT);
  pinMode(PINO_ECHO_SENSOR, INPUT);
  pinMode(PINO_LED_VERMELHO, OUTPUT);
  pinMode(PINO_LED_VERDE, OUTPUT);
  pinMode(PINO_CAMPAINHA, OUTPUT);
}

void loop() {
  long tempoEco, distancia;
  
  //--- gera um pulso no pino trigger do sensor
  digitalWrite(PINO_TRIGGER_SENSOR, LOW);
  delayMicroseconds(2);
  digitalWrite(PINO_TRIGGER_SENSOR, HIGH);
  delayMicroseconds(10);
  digitalWrite(PINO_TRIGGER_SENSOR, LOW);
  
  //--- le atraso da resposta no pino echo
  tempoEco = pulseIn(PINO_ECHO_SENSOR, HIGH);
  //--- o calculo da distancia considera que a velocidade do som = 343.5 m/s
  distancia = (tempoEco/2) / 29.1;
  
  //--- controla os leds e a campainha de acordo com a distancia
  if (distancia < DISTANCIA_ALARME) {
    digitalWrite(PINO_LED_VERMELHO, HIGH);
    digitalWrite(PINO_LED_VERDE, LOW);
    digitalWrite(PINO_CAMPAINHA, HIGH);
  }
  else {
    digitalWrite(PINO_LED_VERMELHO, LOW);
    digitalWrite(PINO_LED_VERDE, HIGH);
    digitalWrite(PINO_CAMPAINHA, LOW);
  }
  
  //--- envia a distancia em cm para o computador
  if (distancia >= 200) {
    Serial.println("Longe demais!");
  } else if (distancia <= 0) {
    Serial.println("Perto demais...");
  }
  else {
    Serial.print(distancia);
    Serial.println(" cm");
  }
  
  //--- da um tempo e comeca de novo
  delay(500);
}
