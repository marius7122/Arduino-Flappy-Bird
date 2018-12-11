#ifndef DISPLAY_CONTROLER
#define DISPLAY_CONTROLER

#include "LedControl.h"

#define PIN_DIN 12
#define PIN_LOAD 10
#define PIN_CLK 11

#define INTENSITY 1

class Display
{
    LedControl lc = LedControl(PIN_DIN, PIN_CLK, PIN_LOAD, 1);
    bool rotated = false;

    static Display* instance;
    Display();
    
public:
    static Display* getInstance();

    void setPixel(byte row, byte col, bool state);
    void setCol(byte col, byte value);
    void setRow(byte row, byte value);
    void rotate90();

};

#endif