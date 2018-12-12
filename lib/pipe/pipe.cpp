#include "pipe.h"
#include <Arduino.h>

int Pipe::pipeNumber = 0;
Display* Pipe::display = Display::getInstance();

Pipe::Pipe()
{
    pipeNumber++;

    speed = START_SPEED + pipeNumber * PIXEL_DISTANCE * 0.1;
    speed = min(speed, MAX_SPEED);
    posX = 8 * PIXEL_DISTANCE;
    outOfDisplay = false;
    lastUpdate = millis();

    gapPosition = random(0, 8 - GAP_SIZE + 1);  // +1 because is exclusive

    pipeShape = B11111111;
    for(int i = 0; i < GAP_SIZE; i++)
        pipeShape -= (1 << (i + gapPosition));     // unset bit i
}

void Pipe::updatePosition()
{
    if(outOfDisplay)
        return;

    unsigned long currentTime = millis();
    unsigned long deltaTime = currentTime - lastUpdate;
    
    posX -= deltaTime * 0.001 * speed;

    if(posX < 0)
    {
        outOfDisplay = true;
        display->setCol(currPixelPosition, B00000000);  // delete pipe from display
        currPixelPosition = -1;
        return;
    }

    byte newPixelPosition = (int)(posX / PIXEL_DISTANCE);
    
    if(newPixelPosition != currPixelPosition)
        moveTo(newPixelPosition);

    lastUpdate = currentTime;
}

void Pipe::moveTo(byte newPixelPosition)
{
    // turn off anterior position
    display->setCol(currPixelPosition, B00000000);

    currPixelPosition = newPixelPosition;

    //turn on new positon
    display->setCol(currPixelPosition, pipeShape);
}

bool Pipe::onDisplay()
{
    return !outOfDisplay;
}

void Pipe::reset()
{
    *this = Pipe();
}