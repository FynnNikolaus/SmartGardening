/*
 *  Titel:    MyGubbins Gartenhaus 
 *  Date:     02.01.2021
 *  Writer:   Fynn Nikolaus ©
 *  License:  GNU Affero General Public License v3.0
 *  Website:  www.mygubbins.org
 */

// Basic librarys 
#include <Arduino.h>

// Display librarys 
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Air sensor library
#include "DHT.h"
#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

int pinPumpOne = 13;

int pinLedOne = 12;
int pinLedTwo = 11;


void setup() {

  Serial.begin(9600);
  u8g2.begin();
  dht.begin();
  pinMode(pinPumpOne, OUTPUT);
  pinMode(pinLedOne, OUTPUT);
  pinMode(pinLedTwo, OUTPUT);
  
}


void loop() {

  int humiditySensorOne = SoilMeasurement(analogRead(A0));
  int humiditySensorTwo = SoilMeasurement(analogRead(A1));
  int humiditySensorThree = SoilMeasurement(analogRead(A2));

  byte minimumHumidity = 55;
  byte wateringTime = 7000; 
  
  if (humiditySensorOne < minimumHumidity &&
      humiditySensorTwo < minimumHumidity &&
      humiditySensorThree < minimumHumidity){
        
        digitalWrite(pinPumpOne, LOW);
        delay(wateringTime);
        digitalWrite(pinPumpOne, HIGH);
      }

  DisplaySoilHumidityPage(humiditySensorOne, humiditySensorTwo, humiditySensorThree);
  delay(3000);

  
  long airTemperature = dht.readTemperature();
  long airHumidity = dht.readHumidity();

  DisplayAirQualityPage(airTemperature, airHumidity);
  delay(3000);
}


int SoilMeasurement(int soilSensor){
  
  int _ocean = 360; 
  int _desert = 630;
  
  int humidityValue = map(soilSensor, _ocean, _desert, 100, 0); 

  
  if (humidityValue > 100) {
        humidityValue = 100;
  }
  else if (humidityValue < 0) {
             humidityValue = 0;
  }

  return humidityValue;
  
}

void DisplaySoilHumidityPage(int sensorOne, int sensorTwo, int sensorThree){

  u8g2.clearBuffer(); 
  u8g2.setFont(u8g2_font_helvB08_tf); 
  u8g2.drawStr(0,10,"Soil humidity");
  u8g2.drawHLine(0, 15, 120);
  u8g2.setCursor(0, 32);
  u8g2.print("Sensor 1: ");
  u8g2.print(sensorOne); 
  u8g2.print(" %");;
  u8g2.setCursor(0, 45);
  u8g2.print("Sensor 2: ");
  u8g2.print(sensorTwo);
  u8g2.print(" %");
  u8g2.setCursor(0, 58);
  u8g2.print("Sensor 3: ");
  u8g2.print(sensorThree);
  u8g2.print(" %");
  u8g2.sendBuffer();
}

void DisplayAirQualityPage(long temperatureValue, long humidityValue){

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvB08_tf); 
  u8g2.drawStr(0,10,"Air quality");
  u8g2.drawHLine(0, 15, 120);
  u8g2.setCursor(0, 32);
  u8g2.print("Temperature: ");
  u8g2.print(temperatureValue); 
  u8g2.print(" *C");
  u8g2.setCursor(0, 45);
  u8g2.print("Humidity: ");
  u8g2.print(humidityValue);
  u8g2.print(" %");
  u8g2.sendBuffer();
}
