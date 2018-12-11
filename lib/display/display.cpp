#include "display.h"

static Display* Display::instance = nullptr;

Display::Display()
{
    lc.shutdown(0, false);
    lc.setIntensity(0, INTENSITY);
    lc.clearDisplay(0);
}

static Display* Display::getInstance()
{
    if(instance == nullptr)
        instance = new Display();
    
    return instance;
}

void Display::setPixel(byte row, byte col, bool state)
{
    if(rotated)
        lc.setLed(0, col, row, state);
    else
        lc.setLed(0, row, col, state);
}

void Display::setRow(byte row, byte value)
{
    if(rotated)
        lc.setColumn(0, row, value);
    else
        lc.setRow(0, row, value);
}

void Display::setCol(byte col, byte value)
{
    if(rotated)
        lc.setRow(0, col, value);
    else
        lc.setColumn(0, col, value);
}

void Display::rotate90()
{
    rotated = true;
}