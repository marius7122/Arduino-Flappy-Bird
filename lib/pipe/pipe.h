#ifndef PIPE_H 
#define PIPE_H

#include "display.h"

#define GAP_SIZE    3
#define START_SPEED 1
#define MAX_SPEED   2

class Pipe
{
    float   speed;
    byte    xPosition;
    byte    gapPosition;    // bottom position of gap
    byte    pipeShape;
    
    static Display *display;
    static int pipeNumber;  // number of pipes, used to constantly increase pipe speed

public:
    Pipe();

};

#endif