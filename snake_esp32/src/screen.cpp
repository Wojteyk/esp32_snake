#include <Arduino.h>
#include "header.h"
#include <TFT_eSPI.h> 
#include <SPI.h>

enum Screens{
    main,
    game,
    gameover,
};

constexpr uint16_t background = TFT_BLACK;
TFT_eSPI tft = TFT_eSPI();
Screens typeScreen = main;
object apple;
dir previousDir;

void gameScreen(){
    drawApple();
    drawSnake();
    joystickMoves();
}

void mainScreen(){
    tft.drawCentreString("Snake", 80,40,2); 
    tft.drawCentreString("press any button", 80,60,1); 
    tft.drawCentreString("to start game",80,75,1);
}

void chooseScreen(){
    if((typeScreen == main || typeScreen == gameover) && isButtonPressed()){
        typeScreen = game;
        tft.fillScreen(background);
        initGame();
    }
    switch (typeScreen)
    {
    case game:
        gameScreen();
        break;
    case main:
        mainScreen();
        break;
    case gameover:
        gameoverScreen();
        break;
    }

}

void initScreen(){
    tft.init();
    tft.setRotation(1); 
    tft.fillScreen(background);
    tft.setTextColor(TFT_BLUE, background); 
    tft.setTextSize(1);
}

void drawSnake(){

snake.currentmilis = millis();

    if(snake.currentmilis - snake.startMilis >= 70){
        snake.startMilis = snake.currentmilis; 
    
    // earsing snake head before
    tft.fillCircle(snake.xPos,snake.yPos,snake.size,background);

    if(snake.length > 0){
         //erasing last segment
        tft.fillCircle(snake.bodyX[snake.length-1], snake.bodyY[snake.length-1], snake.size, background);
        
        for(int i = snake.length -1; i > 0; i-- ){
        snake.bodyX[i]= snake.bodyX[i-1];
        snake.bodyY[i]= snake.bodyY[i-1];
        }

        snake.bodyX[0]= snake.xPos;
        snake.bodyY[0]= snake.yPos;

    //drawig new first segmnet
    tft.fillCircle(snake.bodyX[0], snake.bodyY[0], snake.size, TFT_GREEN);
    }
    // Serial.print("teraz");
    // Serial.println(snake.direction);
    // Serial.print("poprzednia");
    // Serial.println(previousDir);
    switch (snake.direction){
        case left:
        if(previousDir != right){
             snake.xPos -=4; 
        }else{
            snake.direction=right;
            snake.xPos +=4;
        }
        break;
        case right:
        if(previousDir != left){
             snake.xPos +=4; 
        }else{
            snake.direction=left;
            snake.xPos -=4;
        }
        break;
        case down:
        if(previousDir != up){
             snake.yPos +=4;
        }else{
            snake.direction=up;
            snake.yPos -=4;
        }
        break;
        case up: 
        if(previousDir != down){
            snake.yPos -=4; 
        }else{
            snake.direction=down;
            snake.yPos +=4;
        }
        break;
    }

    previousDir = snake.direction;

    for(int i=0; i < snake.length; i++){
        if(abs(snake.xPos - snake.bodyX[i]) < 4 && abs(snake.yPos - snake.bodyY[i]) < 4){
        initGameoverScreen();
        return;
        }
    }
    //draw head
    tft.fillCircle(snake.xPos,snake.yPos,snake.size,TFT_GREEN);
    tft.fillCircle(snake.xPos+2,snake.yPos-2,2,background);
    }
}

void drawApple(){
     //drawing apples after harvest
    if(isAppleHarvested){

        snake.length++;
        snake.score++;
        isAppleHarvested=false;
        tft.fillCircle(apple.xPos,apple.yPos,apple.size,background);
        apple.xPos = random(30,120);
        apple.yPos = random(30,100);

        for(int i=0; i < snake.length; i++){
            if(abs(apple.xPos- snake.bodyX[i]) < 4 && abs(apple.yPos - snake.bodyY[i]) < 4){
                apple.xPos = random(30,120);
                apple.yPos = random(30,100);
        }
    }
    }
    tft.fillCircle(apple.xPos,apple.yPos,apple.size,TFT_RED);
}

void initMainScreen(){
    typeScreen = main;
    tft.fillScreen(background);
}

void initGameoverScreen(){
    typeScreen = gameover;
    tft.fillScreen(background);

}

void gameoverScreen(){
    tft.setCursor(77,40);
    tft.print(snake.score);
    tft.drawCentreString("press any button", 80,60,1); 
    tft.drawCentreString("to start game",80,75,1);
}