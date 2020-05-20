/*
 *  Titel:    MyGubbins Gartenhaus 
 *  Date:     10.04.2020
 *  Writer:   Fynn Nikolaus ©
 *  License:  GNU Affero General Public License v3.0
 *  Website:  www.mygubbins.org
 */
 
// Temperature and humidity meter libraries
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 2 
#define DHTTYPE    DHT11

//Display libraries
#include <Arduino.h>
#include <U8g2lib.h>


//Garden house libraries
#include "AirSensor.h"


 
// Define Relai pins
const int RELAI1 = 1; 
const int RELAI2 = 2; 
const int RELAI3 = 3; 



void setup() {
// Relais
pinMode(RELAI1, OUTPUT);
pinMode(RELAI2, OUTPUT);
pinMode(RELAI3, OUTPUT);
pinMode(RELAI4, OUTPUT);
pinMode(RELAI5, OUTPUT);

u8g2.begin();

}

void loop() {
u8g2.clearBuffer();                     // clear the internal memory
u8g2.setFont(u8g2_font_ncenB08_tr);     // choose a suitable font
u8g2.drawStr(0,10,"Hello world!"); // write something to the internal memory
u8g2.sendBuffer();                      // transfer internal memory to the display
digitalWrite(RELAI1, LOW);
digitalWrite(RELAI2, HIGH);
delay(100);
digitalWrite(RELAI1, LOW);
delay(800);

}
