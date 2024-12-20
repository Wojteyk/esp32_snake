#include <Arduino.h>
#include "header.h"
#include <TFT_eSPI.h> 
#include <SPI.h>

#define yPin 25
#define xPin 32
#define swPin 33

struct button{
  long startMilis;
  long currentmilis; 
  int value;
};

struct controler
{
  int xPos; 
  int yPos;
  long startMilis;
  long currentmilis; 
  dir direction;
  
};

controler joystick; 
button presser;
object snake;
bool isAppleHarvested = true;

bool isButtonPressed(){
    presser.currentmilis = millis();
  if(presser.currentmilis - presser.startMilis >= 300){
    if(!digitalRead(swPin)){
      return true;
    }else{
      return false;
    }
    presser.startMilis = presser.currentmilis;
  }
}

void joystickMoves(){
  
    joystick.currentmilis = millis();
    if(joystick.currentmilis - joystick.startMilis >= 100){
      joystick.startMilis = joystick.currentmilis;
      
      joystick.xPos = analogRead(xPin);
      joystick.yPos = analogRead(yPin);

        dir newDirection = snake.direction; // Preserve the current direction

        if (joystick.xPos > 2500) {
            newDirection = right;
        } else if (joystick.xPos < 1500) {
            newDirection = left;
        } else if (joystick.yPos > 2500) {
            newDirection = down;
        } else if (joystick.yPos < 1500) {
            newDirection = up;
        }

        // Update only if the new direction is different
        if (newDirection != snake.direction) {
            snake.direction = newDirection;
        }
      }

      if(abs(snake.xPos-apple.xPos) < 5 && abs(snake.yPos - apple.yPos) < 5){
        isAppleHarvested=true;
      }
      //checking borders
      if(snake.xPos > 155 || snake.xPos < 5|| snake.yPos< 5 || snake.yPos > 123){
        initGameoverScreen();
      }
  }

void init(){
    initScreen();
    pinMode(xPin, INPUT_PULLUP);
    pinMode(yPin, INPUT_PULLUP);
    pinMode(swPin, INPUT_PULLUP);
    
}

void initGame(){
  //default game settings
    previousDir = up;
    isAppleHarvested=1;
    snake.xPos= 10;
    snake.yPos= 118;
    snake.size = 4;
    snake.length = -1;
    snake.direction = up;
    snake.score = -1;
    apple.size = 4;
    snake.startMilis = millis();
}




