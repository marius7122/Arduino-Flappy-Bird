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
    byte currPixelPosition;     // current colomn
    bool outOfDisplay;          // is true when pipe get out of the screen
    
    static Display *display;
    static int pipeNumber;  // number of pipes, used to constantly increase pipe moving speed

    void moveTo(byte newPixelPosition);

public:
    Pipe();
    void updatePosition();
    bool onDisplay();
    void reset();
};

#endif