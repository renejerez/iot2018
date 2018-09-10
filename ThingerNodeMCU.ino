/*********************************************************/
/*Bibliotecas e Definições para conexão com a thinger.IO**/ 
/*********************************************************/
#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "usuario"
#define DEVICE_ID "nome do device"
#define DEVICE_CREDENTIAL "credenciais"

#define SSID "nome da rede"
#define SSID_PASSWORD "senha da rede"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);


/*********************************************************/
/*Bibliotecas e Definições para medição de temperatura****/
/*********************************************************/
#include <OneWire.h>
#include <DallasTemperature.h>

#define SENSOR_PIN 14

OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);


void setup() {
  Serial.begin(9600);

thing.add_wifi(SSID, SSID_PASSWORD);

 /*********************************************************/
/********Carregar os leds vermelho, amarelo e verde********/
/**********************************************************/
  setupLedVermelho();
  setupLedAmarelo();
  setupLedVerde();
 
  thing["ledvermelho"] << digitalPin(16);
  thing["ledamarelo"] << digitalPin(5);
  thing["ledverde"] << digitalPin(4);
 
 /*********************************************************/
/******Carregar os valores da Temperatura do sensor********/
/**********************************************************/
  thing["temperatura"] >> [](pson& out){  
  DS18B20.requestTemperatures(); 
  out = DS18B20.getTempCByIndex(0);  
  }; 
}

void loop() {
  thing.handle();
}
 
/*********************************************************/
/****Declaração dos leds vermelho, amarelo e verde********/
/*********************************************************/
void setupLedVermelho() {
  pinMode(16, OUTPUT);
}

void setupLedAmarelo() {
  pinMode(5, OUTPUT);
}


void setupLedVerde() {
  pinMode(4, OUTPUT);
}
 
/*********************************************************/
/*********Declaração da Leitura de Temperatura************/
/*********************************************************/
/*
  unsigned float lerTemperatura() {
  float temp;
  DS18B20.requestTemperatures(); 
  temp = DS18B20.getTempCByIndex(0);
  return temp;
}
*/
