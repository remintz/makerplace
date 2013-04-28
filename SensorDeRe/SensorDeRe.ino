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
int PINO_CAMPAINHA = 9;

int DISTANCIA_ZONA_1 = 30;
int DISTANCIA_ZONA_2 = 20;
int DISTANCIA_ZONA_3 = 10;
int DISTANCIA_ZONA_4 = 5;

int DURACAO_CAMPAINHA = 100;
int INTERVALO_ZONA_1 = 5000;
int INTERVALO_ZONA_2 = 1000;
int INTERVALO_ZONA_3 = 200;

int DURACAO_CICLO = 100;
int PERIODO_EXIBE_DISTANCIA = 1000 / DURACAO_CICLO;

int zonaAlerta = 0;
boolean alertaLigado = false;
boolean campainhaLigada = false;
int contaCiclos = 0;
int contaCicloExibeDistancia = 0;

void setup() {
  Serial.begin (9600);
  pinMode(PINO_TRIGGER_SENSOR, OUTPUT);
  pinMode(PINO_ECHO_SENSOR, INPUT);
  pinMode(PINO_CAMPAINHA, OUTPUT);
}

void loop() {
  long tempoEco, distancia;
  boolean ligaAlerta = false;
  
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
  
  //--- verifica em que faixa de distancia o obstaculo se encontra
  if (distancia < DISTANCIA_ZONA_4) {
    ligaAlerta = true;
    zonaAlerta = 4;
  } else if (distancia < DISTANCIA_ZONA_3) {
    ligaAlerta = true;
    zonaAlerta = 3;
  } else if (distancia < DISTANCIA_ZONA_2) {
    ligaAlerta = true;
    zonaAlerta = 2;
  } else if (distancia < DISTANCIA_ZONA_1) {
    ligaAlerta = true;
    zonaAlerta = 1;
  } else {
    //--- obstaculo esta distante
    zonaAlerta = 0;
    alertaLigado = false;
    if (campainhaLigada) {
      digitalWrite(PINO_CAMPAINHA, LOW);
      campainhaLigada = false;
    }
  }

//--- controle da campainha
if (alertaLigado) {
  if ((zonaAlerta > 0) && (zonaAlerta < 4)) {
    //--- a campainha so fica ligada um ciclo
    if (campainhaLigada) {
      digitalWrite(PINO_CAMPAINHA, LOW);
      campainhaLigada = false;
    }
    //--- verifica se eh hora de ligar novamente
    contaCiclos = contaCiclos - 1;
    if (contaCiclos < 0) {
      //--- ta na hora
      digitalWrite(PINO_CAMPAINHA, HIGH);
      campainhaLigada = true;
      //--- calcula quando deve ser ligada novamente
      switch (zonaAlerta) {
        case 1:
          contaCiclos = INTERVALO_ZONA_1 / DURACAO_CICLO;
          break;
        case 2:
          contaCiclos = INTERVALO_ZONA_2 / DURACAO_CICLO;
          break;
        case 3:
          contaCiclos = INTERVALO_ZONA_3 / DURACAO_CICLO;
          break;
        default:
          break;
      }
    }
  }
} else {
  //--- o alerta nao estava ligado
  if (ligaAlerta) {
    //--- veio um comando para ligar o alerta
    digitalWrite(PINO_CAMPAINHA, HIGH);
    campainhaLigada = true;
    ligaAlerta = false;
    alertaLigado = true;
  }
}
  
//--- a exibicao da distancia nao acontece em todos os ciclos
contaCicloExibeDistancia -= 1;
if (contaCicloExibeDistancia < 0) {
  contaCicloExibeDistancia = PERIODO_EXIBE_DISTANCIA;
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
}
  
  //--- da um tempo e comeca de novo
  delay(DURACAO_CICLO);
}
