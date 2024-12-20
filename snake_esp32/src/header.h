
#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

enum dir {
    up,
    down,
    left,
    right
};


struct object{
    int score;
    int xPos;
    int yPos;
    int size;
    int length;
    int bodyX[50];
    int bodyY[50];
    unsigned long currentmilis;
    unsigned long startMilis;
    dir direction;
};

extern object snake;
extern object apple;
extern bool isAppleHarvested;
extern dir previousDir;

void joystickMoves();
bool isButtonPressed();
void init();
void initGame();
void mainScreen();
void gameScreen();
void chooseScreen();
void initScreen();
void drawSnake();
void initMainScreen();
void drawApple();
void initGameoverScreen();
void gameoverScreen();

#endif