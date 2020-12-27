/*
 *  Titel:    MyGubbins Gartenhaus 
 *  Date:     10.04.2020
 *  Writer:   Fynn Nikolaus ©
 *  License:  GNU Affero General Public License v3.0
 *  Website:  www.mygubbins.org
 */

// Basic librarys 
#include <Arduino.h>
#include <Async_Operations.h> // https://github.com/DaniFoldi/Async_Operations

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
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int pinPumpOne = 13;


void setup() {

  u8g2.begin();
  dht.begin();
  pinMode(pinPumpOne, OUTPUT);
  
}


void loop() {

  int _ocean = 360; 
  int _desert = 630;
  
  int humiditySensorOne = map(analogRead(A0), _ocean, _desert, 100, 0);
  int humiditySensorTwo = map(analogRead(A1), _ocean, _desert, 100, 0);
  int humiditySensorThree = map(analogRead(A2), _ocean, _desert, 100, 0);
  float airTemperature = 0;
  float airHumidity = 0;

  if (humiditySensorOne > 100) {
        humiditySensorOne = 100;
  }
  else if (humiditySensorOne < 0) {
             humiditySensorOne = 0;
  }

  if (humiditySensorTwo > 100) {
        humiditySensorTwo = 100;
  }
  else if (humiditySensorTwo < 0) {
             humiditySensorTwo = 0;
  }
  if (humiditySensorThree > 100) {
        humiditySensorThree = 100;
  }
  else if (humiditySensorThree < 0) {
             humiditySensorThree = 0;
  }

  int minimumHumidity = 55;
  
  if (humiditySensorOne < minimumHumidity &&
      humiditySensorTwo < minimumHumidity &&
      humiditySensorThree < minimumHumidity){
        
        digitalWrite(pinPumpOne, HIGH);
        delay(3000);
        digitalWrite(pinPumpOne, LOW);
      }

  
  u8g2.clearBuffer(); 
  u8g2.setFont(u8g2_font_helvB08_tf); 
  u8g2.drawStr(0,10,"Soil humidity");
  u8g2.drawHLine(0, 15, 120);
  u8g2.setCursor(0, 32);
  u8g2.print("Sensor 1: ");
  u8g2.print(humiditySensorOne); 
  u8g2.print(" %");;
  u8g2.setCursor(0, 45);
  u8g2.print("Sensor 2: ");
  u8g2.print(humiditySensorTwo);
  u8g2.print(" %");
  u8g2.setCursor(0, 58);
  u8g2.print("Sensor 3: ");
  u8g2.print(humiditySensorThree);
  u8g2.print(" %");
  u8g2.sendBuffer();
  //delay(8000); 

  /*
  airTemperature = dht.readTemperature();
  airHumidity = dht.readHumidity();
  
  if (isnan(airTemperature) || isnan(airHumidity)) { 
    
    u8g2.clearBuffer();     
    u8g2.setFont(u8g2_font_helvB08_tf); 
    u8g2.drawStr(0,10,"Air quality: Error!");
    u8g2.sendBuffer();
    delay(2000); 
   
  }

  else{
  u8g2.clearBuffer(); 
  u8g2.setFont(u8g2_font_helvB08_tf); 
  u8g2.drawStr(0,10,"Air quality");
  u8g2.drawHLine(0, 15, 120);
  u8g2.setCursor(0, 32);
  u8g2.print("Temperature: ");
  u8g2.print((float)airTemperature); 
  u8g2.print(" *C");
  u8g2.setCursor(0, 45);
  u8g2.print("Humidity: ");
  u8g2.print((float)airHumidity);
  u8g2.print(" %");
  u8g2.sendBuffer();
  delay(8000); 
  } 
  */
}
