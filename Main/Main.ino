/*
 *  Titel:    MyGubbins Gartenhaus 
 *  Date:     10.04.2020
 *  Writer:   Fynn Nikolaus ©
 *  License:  GNU Affero General Public License v3.0
 *  Website:  www.mygubbins.org
 */
 
#include <Arduino.h>

//Display librarys 
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


void setup() {
  
  u8g2.begin();
}


void loop() {
  
  int _ocean = 155; 
  int _desert = 380;
  
  byte humiditySensorOne = map(analogRead(A0), _ocean, _desert, 100, 0);
  byte humiditySensorTwo = map(analogRead(A1), _ocean, _desert, 100, 0);
  byte humiditySensorThree = map(analogRead(A2), _ocean, _desert, 100, 0);

  u8g2.clearBuffer(); 
  
  u8g2.firstPage();
  do{
  u8g2.setFont(u8g2_font_helvB08_tf); 
  u8g2.drawStr(0,10,"Relative humidity");
  u8g2.setCursor(0, 30);
  u8g2.print("Sensor 1: ");
  u8g2.print(humiditySensorOne); 
  u8g2.print(" %");
  u8g2.setCursor(0, 43);
  u8g2.print("Sensor 2: ");
  u8g2.print(humiditySensorTwo);
  u8g2.print(" %");
  u8g2.setCursor(0, 56);
  u8g2.print("Sensor 3: ");
  u8g2.print(humiditySensorThree);
  u8g2.print(" %");
  u8g2.sendBuffer();          
  }while(u8g2.nextPage());
  
  delay(1000);   
}
