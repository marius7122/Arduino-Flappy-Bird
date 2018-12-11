#ifndef BIRD_H
#define BIRD_H

#include "display.h"

#define GRAVITY         170
#define JUMP_VELOCITY   70
#define PIXEL_DISTANCE  10      // virtual distance between pixels
#define POS_X           1
#define START_LED_Y     7
#define MIN_SPEED       JUMP_VELOCITY / 2

class Bird
{
public:
    float   posY;
    float   velocity;
    int     birdLedY;           // row of led which represent bird
    unsigned long lastUpdate;   // last time when bird position was updated

    Display *display;

    Bird();
    void updatePosition();
    void moveBird(int newLedY);
    void drawBird();
    void jump();
};

#endif