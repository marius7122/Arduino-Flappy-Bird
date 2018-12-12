#ifndef BIRD_H
#define BIRD_H

#include "display.h"

#define GRAVITY         170
#define JUMP_VELOCITY   70
#define POS_X           1
#define START_LED_Y     7
#define MIN_SPEED       JUMP_VELOCITY / 2

class Bird
{
    float   posY;
    float   velocity;
    byte    birdLedY;           // row of led which represent bird
    unsigned long lastUpdate;   // last time when bird position was updated
    bool dead;

    Display *display;

    void searchColision();

public:
    Bird();
    void updatePosition();
    void moveBird(int newLedY);
    void drawBird();
    void jump();
    bool isDead();
};

#endif