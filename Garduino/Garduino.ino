/*
Relay: In1 = Bomba; In2 = Lampada

*/
//BIBLIOTECAS
#include <OneWire.h>
#include <DallasTemperature.h>


//PINAGEM

#define ONE_WIRE_BUS 12 // Sensor de temperatura
#define TEMP_GATILHO 15 //EM GRAUS
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;

const int sensorUmidade = A2;

//Pinos do Display de 7 segmentos
const int digit1 = 5;
const int digit2 = 8;
const int digit3 = 9;
const int digit4 = 4;

const int segA = 6;
const int segB = 10;
const int segC = 2;
const int segD = 1;
const int segE = 0;
const int segF = 7;
const int segG = 3;

const int buttonPin = 13;
const int relayBomba = A0;
const int relayLampada = A1;


#define UPDATE_INTERVAL 0.1 //Tempo de espera (aproximado) em minutos até a proxima leitura
const int intervalIterations = (UPDATE_INTERVAL*50)*60; //Cada iteração equivale a 20ms (usado na função)

#define RELAY_ON LOW
#define RELAY_OFF HIGH

#define BUTTON_ON HIGH
#define BUTTON_OFF LOW

/*
Obs: Por causa da atualização frequente do display, esse UPDATE_INTERVAL se faz necessário, senão ele fica piscando loucamente...
*/

int temperatura; // Variável que armazenará a temperatura medida
int umidade;



void setup(void) {
  sensors.begin();
  sensors.getAddress(sensor1, 0);

  pinMode(buttonPin, INPUT);
  pinMode(relayBomba, OUTPUT);
  pinMode(relayLampada, OUTPUT);

  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);

  pinMode(13, OUTPUT);
  
  digitalWrite(relayBomba, RELAY_OFF);
  digitalWrite(relayLampada, RELAY_OFF);
  
}

void loop() {
  
  //digitalWrite(relayBomba, RELAY_OFF);
  
  // Le a informacao do sensor
  sensors.requestTemperatures();
  float tempC = sensors.getTempC(sensor1);
  
  temperatura = round(tempC);
  
  umidade = analogRead(sensorUmidade);
  
  int reading = digitalRead(buttonPin);
  if (reading == BUTTON_ON){
    // RELAY LIGADO
    digitalWrite(relayBomba, RELAY_ON);
    digitalWrite(relayLampada, RELAY_ON);
    //Serial.println("Ta HIGH");
  }
  else if(reading == BUTTON_OFF){
    // RELAY DESLIGADO
    //digitalWrite(relayBomba, RELAY_OFF);
    //digitalWrite(relayLampada, RELAY_OFF);
    //Serial.println("Ta LOW");
  }
 
  
  if(temperatura <= TEMP_GATILHO){
    digitalWrite(relayLampada, RELAY_ON);
  }
  else {
    digitalWrite(relayLampada, RELAY_OFF);
  }
  
  
  //Solo umido 0 - 600
 
  //Solo com umidade moderada 600 - 800
 
  //Solo seco
  if (umidade > 800 && umidade < 1024)
  {
    digitalWrite(relayBomba, RELAY_ON);
  }
  
  else if (umidade < 800)
  {
    digitalWrite(relayBomba, RELAY_OFF);
  }

  for(int i = 0; i < intervalIterations; i++) {
    displayNumber(temperatura);
  }
  
}

void displayNumber(int toDisplay) {

#define DISPLAY_BRIGHTNESS  500
#define DIGIT_ON  HIGH
#define DIGIT_OFF  LOW

  int digitos[4] = { toDisplay/10, toDisplay%10, 11, 12 };

  long beginTime = millis();

  for(int digit = 4 ; digit > 0 ; digit--) {
    toDisplay = digitos[digit - 1];

    //Turn on a digit for a short amount of time
    switch(digit) {
    case 1:
      digitalWrite(digit1, DIGIT_ON);
      break;
    case 2:
      digitalWrite(digit2, DIGIT_ON);
      break;
    case 3:
      digitalWrite(digit3, DIGIT_ON);
      break;
    case 4:
      digitalWrite(digit4, DIGIT_ON);
      break;
    }

    //Turn on the right segments for this digit
    lightNumber(toDisplay);

    delayMicroseconds(DISPLAY_BRIGHTNESS);
    //Display digit for fraction of a second (1us to 5000us, 500 is pretty good)

    //Turn off all segments
    lightNumber(10);

    //Turn off all digits
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);
  }

  while( (millis() - beginTime) < 10) ;
  //Wait for 20ms to pass before we paint the display again
}

void displayStandBy() {

#define DISPLAY_BRIGHTNESS  500
#define DIGIT_ON  HIGH
#define DIGIT_OFF  LOW

  int digitos[4] = { 16, 16, 16, 16 };
  int toDisplay = 0;

  long beginTime = millis();

  for(int digit = 4 ; digit > 0 ; digit--) {
    toDisplay = digitos[digit - 1];

    //Turn on a digit for a short amount of time
    switch(digit) {
    case 1:
      digitalWrite(digit1, DIGIT_ON);
      break;
    case 2:
      digitalWrite(digit2, DIGIT_ON);
      break;
    case 3:
      digitalWrite(digit3, DIGIT_ON);
      break;
    case 4:
      digitalWrite(digit4, DIGIT_ON);
      break;
    }

    //Turn on the right segments for this digit
    lightNumber(toDisplay);

    delayMicroseconds(DISPLAY_BRIGHTNESS);
    //Display digit for fraction of a second (1us to 5000us, 500 is pretty good)

    //Turn off all segments
    lightNumber(10);

    //Turn off all digits
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);
  }

  while( (millis() - beginTime) < 10) ;
  //Wait for 20ms to pass before we paint the display again
}

void displayLoad() {

#define DISPLAY_BRIGHTNESS  500
#define DIGIT_ON  HIGH
#define DIGIT_OFF  LOW

  int digitos[4] = { 13, 0, 14, 15 };
  int toDisplay = 0;

  long beginTime = millis();

  for(int digit = 4 ; digit > 0 ; digit--) {
    toDisplay = digitos[digit - 1];

    //Turn on a digit for a short amount of time
    switch(digit) {
    case 1:
      digitalWrite(digit1, DIGIT_ON);
      break;
    case 2:
      digitalWrite(digit2, DIGIT_ON);
      break;
    case 3:
      digitalWrite(digit3, DIGIT_ON);
      break;
    case 4:
      digitalWrite(digit4, DIGIT_ON);
      break;
    }

    //Turn on the right segments for this digit
    lightNumber(toDisplay);

    delayMicroseconds(DISPLAY_BRIGHTNESS);
    //Display digit for fraction of a second (1us to 5000us, 500 is pretty good)

    //Turn off all segments
    lightNumber(10);

    //Turn off all digits
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);
  }

  while( (millis() - beginTime) < 10) ;
  //Wait for 20ms to pass before we paint the display again
}

void lightNumber(int numberToDisplay) {

#define SEGMENT_ON  LOW
#define SEGMENT_OFF HIGH

  switch (numberToDisplay){

  case 0: // NÚMERO 0
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 1: // NÚMERO 1
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 2: // NÚMERO 2
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 3: // NÚMERO 3
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 4: // NÚMERO 4
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 5: // NÚMERO 5
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 6: // NÚMERO 6
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 7: // NÚMERO 7
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 8: // NÚMERO 8
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 9: // NÚMERO 9
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 10: // DIGITO APAGADO
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 11: // SÍMBOLO DE GRAU
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 12: // LETRA C
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 13: // LETRA L
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 14: // LETRA A
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 15: // LETRA d
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;
  case 16: // LETRA -
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;
  }
}

//float leTemperaturaLM35() {
//  return (float(analogRead(pin_sensorTemp))*5/(1023))/0.01;
//}

float leTemperatura() {
  sensors.requestTemperatures();
  return sensors.getTempC(sensor1);
}

int temperaturaMedia() {
  int numero_leituras = 500;
  float temp = 0;

  for(int i = 0; i < numero_leituras; i++){
    temp += leTemperatura();
  }
  temp = temp/numero_leituras;

  return round(temp);
}
