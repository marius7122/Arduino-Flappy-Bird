#ifndef DISPLAY_CONTROLER
#define DISPLAY_CONTROLER

#include "LedControl.h"

#define PIN_DIN 12      // yellow
#define PIN_LOAD 10     // white
#define PIN_CLK 11      // orange

#define INTENSITY 1

#define PIXEL_DISTANCE  10      // virtual distance between pixels

class Display
{
    LedControl lc = LedControl(PIN_DIN, PIN_CLK, PIN_LOAD, 1);
    bool flipped;

    static Display* instance;
    Display();
    
public:
    static Display* getInstance();

    void setPixel(byte row, byte col, bool state);
    void setCol(byte col, byte value);
    void setRow(byte row, byte value);
    void flip();

};

#endif