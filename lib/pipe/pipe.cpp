#include <Arduino.h>
#include "pipe.h"

int Pipe::pipeNumber = 0;
byte Pipe::scoreCnt = 0;
Display* Pipe::display = Display::getInstance();

Pipe::Pipe()
{
    initialize();
}

void Pipe::initialize()
{
    pipeNumber++;

    speed = START_SPEED + pipeNumber * PIXEL_DISTANCE * SPEED_INCREMENT;
    speed = min(speed, MAX_SPEED);
    posX = 8 * PIXEL_DISTANCE;
    outOfDisplay = false;
    lastUpdate = millis();
    inactive = true;

    gapPosition = random(0, 8 - GAP_SIZE + 1);      // +1 because is exclusive

    pipeShape = B11111111;
    for(int i = 0; i < GAP_SIZE; i++)
        pipeShape -= (1 << (i + gapPosition));      // unset bit i
}

void Pipe::updatePosition()
{
    if(outOfDisplay)
        return;
    if(inactive)
        return;

    unsigned long currentTime = millis();
    unsigned long deltaTime = currentTime - lastUpdate;
    
    posX -= deltaTime * 0.001 * speed;

    if(posX < 0)
    {
        outOfDisplay = true;
        deleteFromDisplay();
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
    deleteFromDisplay();

    currPixelPosition = newPixelPosition;

    // pipe is behind bird
    if(currPixelPosition == 0)
    {
        scoreCnt++;
    }

    //turn on new positon
    show();
}

bool Pipe::onDisplay()
{
    return !outOfDisplay;
}

void Pipe::reset()
{
    initialize();
    inactive = false;
}

void Pipe::restart()
{
    pipeNumber = 0;
    scoreCnt = 0;
    deleteFromDisplay();
    initialize();
}

void Pipe::deleteFromDisplay()
{
    byte col = currPixelPosition;
    byte birdPositionX = PipeManager::birdPositionX;
    byte birdPositionY = PipeManager::birdPositionY;

    for(byte row = 0; row < 8; row++)
    {
        PipeManager::setPosition(row, col, false);
        
        // we don want to turn off bird led
        if(col != birdPositionX || row != birdPositionY)
            display->setPixel(row, col, false);
    }
}

void Pipe::show()
{
    byte col = currPixelPosition;
    byte birdPositionX = PipeManager::birdPositionX;
    byte birdPositionY = PipeManager::birdPositionY;
    bool state;

    for(byte row = 0; row < 8; row++)
    {
        state = pipeShape & (1 << row);

        PipeManager::setPosition(row, col, state);

        // we don want to turn off bird led
        if(col != birdPositionX || row != birdPositionY)
            display->setPixel(row, col, state);
    }
}

void Pipe::startMove()
{
    inactive = false;
    lastUpdate = millis();
}

byte Pipe::getScore()
{
    return scoreCnt;
}

bool PipeManager::pipeMatrix[8][8] = { {0} };
byte PipeManager::birdPositionX;
byte PipeManager::birdPositionY;

bool PipeManager::getPosition(byte i, byte j)
{
    delay(1);   // magic, without this doesn't work
    return pipeMatrix[i][j];
}
void PipeManager::setPosition(byte i, byte j, bool state)
{
    pipeMatrix[i][j] = state;
}
void PipeManager::setBirdPosition(byte newPosX, byte newPosY)
{
    birdPositionX = newPosX;
    birdPositionY = newPosY;
}