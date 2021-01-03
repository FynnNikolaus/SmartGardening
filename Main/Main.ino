/*
 *  Titel:    MyGubbins Gartenhaus 
 *  Date:     03.01.2021
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

int pinPumpOne = 13;

void setup() {

  u8g2.begin();
  
  pinMode(pinPumpOne, OUTPUT);
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
        
        digitalWrite(pinPumpOne, HIGH);
        delay(wateringTime);
        digitalWrite(pinPumpOne, LOW);
        delay(300000); 
      }

  DisplaySoilHumidityPage(humiditySensorOne, humiditySensorTwo, humiditySensorThree);
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
  u8g2.print(" %");
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
