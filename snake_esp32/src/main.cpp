#include <Arduino.h>
#include "header.h"



void setup(){
  init();
  Serial.begin(9600);
}

void loop(){
  chooseScreen();
}