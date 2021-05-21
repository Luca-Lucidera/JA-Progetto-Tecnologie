#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"

MAX30105 particleSensor;

#define MAX_BRIGHTNESS 255
#define r1 11 //rosso rgb1
#define g1 10 //verde rgb1
#define b1 9 //blu rgb1
#define r2 8 //rosso rgb2
#define g2 7 //verde rgb2
#define b2 6 //blu rgb2
#define  l1 13 //led1
#define l2 12 //led2
#define btn1 5 //bottone led1
#define btn2 4 //bottone led2
#define btn3 3 //bottone rgb1
#define btn4 2 //bottone rgb2

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
uint16_t irBuffer[100];
uint16_t redBuffer[100];
#else
uint32_t irBuffer[100];
uint32_t redBuffer[100];
#endif

int32_t bufferLength;
int32_t spo2;
int8_t validSPO2;
int32_t heartRate;
int8_t validHeartRate;

byte pulseLED = 11;
byte readLED = 13;
const int sensorPin=A0;
bool starttemp = false;
bool starthr = false;
bool startreflex = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for(int pinNumber=2;pinNumber<5; pinNumber++){
    pinMode(pinNumber,OUTPUT);
    digitalWrite(pinNumber,LOW);
  }
  pinMode(pulseLED, OUTPUT);
  pinMode(readLED, OUTPUT);
  
  Serial.println(F("Attach sensor to finger with rubber band. Press any key to start conversion"));
  while (Serial.available() == 0) ;
  Serial.read();

  byte ledBrightness = 60;
  byte sampleAverage = 4;
  byte ledMode = 2; 
  byte sampleRate = 100;
  int pulseWidth = 411;
  int adcRange = 4096;

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);
  pinMode(r1, OUTPUT);
  pinMode(g1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(g2, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);
}

void loop() {
  if (Serial.available()){
    String tmp = Serial.readStringUntil(';');
    if (tmp == "battito") {
      starthr = true;
    }
    else if (tmp == "temperatura"){
      starttemp = true;
    }
    else if (tmp == "riflessi"){
      startreflex = true;
    }
  };
  // put your main code here, to run repeatedly:
  if (starttemp == true) {
    int sensorVal=analogRead(sensorPin);
    float voltage=(sensorVal/1024.0)*5.0;
    float temperature=(voltage- .5)*100;
    Serial.print("T");
    Serial.println(temperature);
  }
  if (starthr == true) {
    bufferLength = 100;
    
    for (byte i = 0 ; i < bufferLength ; i++)
    {
      while (particleSensor.available() == false)
        particleSensor.check();
  
      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample();
    }
    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
    while (1)
    {
      for (byte i = 25; i < 100; i++)
      {
        redBuffer[i - 25] = redBuffer[i];
        irBuffer[i - 25] = irBuffer[i];
      }
      for (byte i = 75; i < 100; i++)
      {
        while (particleSensor.available() == false)
          particleSensor.check();
  
        digitalWrite(readLED, !digitalRead(readLED));
  
        redBuffer[i] = particleSensor.getRed();
        irBuffer[i] = particleSensor.getIR();
        particleSensor.nextSample();
        
        Serial.print(F("H"));
        Serial.println(heartRate, DEC);
        
        Serial.print(F("S"));
        Serial.println(spo2, DEC);
      }
      maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
    }
  }
  if (startreflex == true) {
    int test;
    test = Test1();
    Serial.print("R");
    Serial.println(test);
  }
}

//test led singoli
int Test1()
{
  int punteggio = 0;
  int tempo = 0;
  int ledOn;
  bool change = true;
  int tempoIniziale, tempoFinale, tempoMax = 1500;
  bool continua = true; //fin quando sei in gioco
  while (continua == true)
  {
    tempoIniziale = millis(); //vedo quando entro
    if (change) {
      ledOn = random(1, 2);
      change = false;
    }
    if (ledOn == 1)
    {
      digitalWrite(l1, HIGH);
      digitalWrite(l2, LOW);
    }
    else
    {
      digitalWrite(l2, HIGH);
      digitalWrite(l1, LOW);
    }

    if (digitalRead(btn1) ==HIGH)
    {
      tempoFinale = millis();
      tempo = tempoFinale - tempoIniziale;
      if (tempo <= tempoMax && ledOn == 1)
      {
        change = true;
        punteggio++;
        continua = true;
        if (tempoMax > 500)
        {
          tempoMax = tempoMax - 500;
        }
      }
      else
      {
        continua = false;
        digitalWrite(l2, LOW);
        digitalWrite(l1, LOW);
        return punteggio;
      }
    }
      else if (digitalRead(btn2)== HIGH)
      {
        tempoFinale = millis();
        tempo = tempoFinale - tempoIniziale;
        if (tempo <= tempoMax && ledOn == 2)
        {
          change = true;
          punteggio++;
          continua = true;
          if (tempoMax > 500)
          {
            tempoMax = tempoMax - 500;
          }
        }
        else
        {
          continua = false;
          digitalWrite(l2, LOW);
          digitalWrite(l1, LOW);
          return punteggio;

        }
      }

    }

  }
