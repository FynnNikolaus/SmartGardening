/*
 *  Titel:    MyGubbins Gartenhaus 
 *  Date:     10.04.2020
 *  Writer:   Fynn Nikolaus ©
 *  License:  GNU Affero General Public License v3.0
 *  Website:  www.mygubbins.org
 */
 
// Temperature and humidity meter libraries
#include <DHT.h>
#define DHTPIN 5 //On pin G5 
#define DHTTYPE DHT11

//Display libraries
#include <U8g2lib.h>
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);



//Garden house libraries
#include "HumiditySensor.h"

//Other libraries
#include <Arduino.h>
 
// Define Relai pins
const int RELAI1 = 13; //On pin G13
const int RELAI2 = 17; //On pin G17
const int RELAI3 = 33; //On pin G33



void setup() {
// Relais
pinMode(RELAI1, OUTPUT); 
pinMode(RELAI2, OUTPUT);
pinMode(RELAI3, OUTPUT);
}

void loop() {

while(true)
{
b
}

}
