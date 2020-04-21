/*
 *  Titel:    MyGubbins Gartenhaus (c)
 *  Datum:    10.04.2020
 *  Autor:    Fynn Nikolaus
 *  Website:  www.mygubbins.org
 */

//Temperatur und Luftfeuchtigkeitsmesser 
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 2 
#define DHTTYPE    DHT11

//Integrierter Display
#include <Arduino.h>
#include <U8g2lib.h>
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

//Gartenhaus Bibliotheken 
#include "Luftsensor.h"
#include "Schrittmotor.h"

 
// Relai Pins
const int RELAI1 = 1; //ESP Pin D1  Strom Pumpe 1
const int RELAI2 = 2; //ESP Pin D2  Strom Pumpe 2
const int RELAI3 = 3; //ESP Pin D3  Strom Pumpe 3
const int RELAI4 = 4; //ESP Pin D4  Strom Schrittmotor 
const int RELAI5 = 5; //ESP Pin D5  Strom Sensoren


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
u8g2.drawStr(0,10,"Funktioniert das?"); // write something to the internal memory
u8g2.sendBuffer();                      // transfer internal memory to the display
digitalWrite(RELAI1, LOW);
digitalWrite(RELAI2, HIGH);
delay(100);
digitalWrite(RELAI1, LOW);
delay(800);

}
