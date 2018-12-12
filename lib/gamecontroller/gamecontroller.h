#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "bird.h"
#include "pipe.h"

#define JUMP_BUTTON_PIN 2
#define JUMP_TIME       200      //minimum time between jumps in miliseconds

class GameController
{
    Bird bird;
    Pipe pipe;
    int score;
    bool gameOver;

    unsigned long lastJump;

public:
    static bool pipeMatrix[8][8];

    GameController();
    void updateFrame();
};

#endif