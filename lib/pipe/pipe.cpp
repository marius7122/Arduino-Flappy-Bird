#include "pipe.h"
#include <Arduino.h>

int Pipe::pipeNumber = 0;
Display* Pipe::display = Display::getInstance();

Pipe::Pipe()
{
    pipeNumber++;

    speed = START_SPEED + pipeNumber * 0.1;
    speed = min(speed, MAX_SPEED);
    xPosition = 8;

    gapPosition = random(0, 8 - GAP_SIZE);

    pipeShape = B11111111;
    for(int i = 0; i < GAP_SIZE; i++)
        pipeShape -= (1 << (i + gapPosition));     // unset bit i

    Serial.println(gapPosition);
    display->setCol(1, pipeShape);
}