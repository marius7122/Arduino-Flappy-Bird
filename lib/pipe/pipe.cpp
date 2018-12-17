#include <Arduino.h>
#include "pipe.h"

int Pipe::pipeNumber = 0;
Display* Pipe::display = Display::getInstance();

Pipe::Pipe()
{
    pipeNumber++;

    speed = START_SPEED + pipeNumber * PIXEL_DISTANCE * SPEED_INCREMENT;
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

    //turn on new positon
    show();
}

bool Pipe::onDisplay()
{
    return !outOfDisplay;
}

void Pipe::reset()
{
    *this = Pipe();
}

void Pipe::deleteFromDisplay()
{
    display->setCol(currPixelPosition, B00000000);

    // unmark pipeMatrix
    for(int row = 0; row < 8; row++)
        PipeManager::setPosition(row, currPixelPosition, false);
}

void Pipe::show()
{
    display->setCol(currPixelPosition, pipeShape);

    // mark pipeMatrix
    for(int row = 0; row < 8; row++)
        PipeManager::setPosition(row, currPixelPosition, pipeShape & (1 << row));
}

bool PipeManager::pipeMatrix[8][8] = { {0} };

bool PipeManager::getPosition(byte i, byte j)
{
    Serial.print("pipemanager: ");
    Serial.println(pipeMatrix[i][j]);
    return pipeMatrix[i][j];
}
void PipeManager::setPosition(byte i, byte j, bool state)
{
    pipeMatrix[i][j] = state;
}