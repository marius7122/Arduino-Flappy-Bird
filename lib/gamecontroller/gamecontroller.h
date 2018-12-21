#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "bird.h"
#include "pipe.h"
#include "display.h"

#define JUMP_BUTTON_PIN 2
#define JUMP_TIME       200      //minimum time between jumps in miliseconds

class GameController
{
    Bird bird;
    Pipe pipe;
    byte score;
    bool gameOver;
    bool gameStarted;

    unsigned long lastJump;
    unsigned long lastScoreUpdate;

    Display *display;

    void startGame();
    void restart();
    void initialize();
    void fadeOut();
    void resetHighscore();

public:
    static bool pipeMatrix[8][8];

    GameController();
    void updateFrame();
};

#endif