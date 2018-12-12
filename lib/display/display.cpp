#include "display.h"

Display* Display::instance = nullptr;

Display::Display()
{
    lc.shutdown(0, false);
    lc.setIntensity(0, INTENSITY);
    lc.clearDisplay(0);
    flipped = true;     // by default display is flipped
}

Display* Display::getInstance()
{
    if(instance == nullptr)
        instance = new Display();
    
    return instance;
}

void Display::setPixel(byte row, byte col, bool state)
{
    if(!flipped)
        lc.setLed(0, row, col, state);
    else
        lc.setLed(0, 7 - row, col, state);
}

void Display::setRow(byte row, byte value)
{
    for(int col = 0; col < 8; col++)
        setPixel(row, 7 - col, value & (1 << col));
}

void Display::setCol(byte col, byte value)
{
    for(int row = 0; row < 8; row++)
        setPixel(row, col, value & (1 << row));
}

void Display::flip()
{
    flipped = !flipped;
}