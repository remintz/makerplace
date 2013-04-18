#define RESOLUCAO 20
#define TIMEOUT_PULSO 30000
#define PINO_SENSOR 2

int iPulso;
int duracaoPulsoAlto;
int duracaoPulsoBaixo;
uint16_t pulsos[100][2];

void setup() {
  Serial.begin(9600);
  Serial.println("Inicio");
  iPulso = 0;
}

void loop() {
  duracaoPulsoAlto = 0;
  duracaoPulsoBaixo = 0;
  //--- mede duracao do pulso alto
  while (PIND & (1 << PINO_SENSOR)) {
    duracaoPulsoAlto++;
    delayMicroseconds(RESOLUCAO);
    if ((duracaoPulsoAlto > TIMEOUT_PULSO) && (iPulso != 0)) {
      //--- estourou tempo apos armazenar pulsos
      mostraPulsos();
      iPulso = 0;
      break;
    }
  } 
  pulsos[iPulso][0] = duracaoPulsoAlto;
  //--- mede duracao do pulso alto
  while ((PIND & 4) == 0) {
    duracaoPulsoBaixo++;
    delayMicroseconds(RESOLUCAO);
    if ((duracaoPulsoBaixo > TIMEOUT_PULSO) && (iPulso != 0)) {
      //--- estourou tempo apos armazenar pulsos
      mostraPulsos();
      iPulso = 0;
      break;
    }
  } 
  pulsos[iPulso][1] = duracaoPulsoBaixo;
  iPulso++;
}

void mostraPulsos(void) {
  Serial.println("\n\r\n\rRecebidos: \n\rBAIXO \tALTO");
  for (int i = 0; i < iPulso-1; i++) {
    Serial.print(pulsos[i][0] * RESOLUCAO, DEC);
    Serial.print(" usec, ");
    Serial.print(pulsos[i][1] * RESOLUCAO, DEC);
    Serial.println(" usec");
  }
}
