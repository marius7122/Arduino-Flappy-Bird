#ifndef PIPE_H 
#define PIPE_H

#include "display.h"

#define GAP_SIZE    3
#define START_SPEED PIXEL_DISTANCE
#define MAX_SPEED   3 * PIXEL_DISTANCE
#define SPEED_INCREMENT 0.1

class Pipe
{
    float   speed;
    float   posX;
    byte    gapPosition;        // top position of gap
    byte    pipeShape;
    unsigned long lastUpdate;
    byte currPixelPosition;     // current column
    bool outOfDisplay;          // is true when pipe get out of the screen
    bool inactive;
    
    static Display *display;
    static int pipeNumber;  // number of pipes, used to constantly increase pipe moving speed
    static byte scoreCnt;


    void moveTo(byte newPixelPosition);
    void deleteFromDisplay();
    void show();
    void initialize();

public:
    Pipe();
    void updatePosition();
    bool onDisplay();
    void reset();
    void restart();
    void startMove();
    byte getScore();
};

class PipeManager
{
    static bool pipeMatrix[8][8];
public:
    static byte birdPositionX, birdPositionY;
    static bool getPosition(byte i, byte j);
    static void setPosition(byte i, byte j, bool state);
    static void setBirdPosition(byte newPosX, byte newPosY);
};


#endif