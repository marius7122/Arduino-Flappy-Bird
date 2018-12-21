#ifndef DISPLAY_CONTROLER
#define DISPLAY_CONTROLER

#include "LedControl.h"
#include <LiquidCrystal.h>

/*      MATRIX CONSTANTS        */
#define PIN_LOAD    10     // white
#define PIN_CLK     11     // orange
#define PIN_DIN     12     // yellow

#define INTENSITY 1

/*      LCD CONSTANTS           */
#define PIN_V0  3
#define PIN_RS  4
#define PIN_E   5
#define PIN_D4  6
#define PIN_D5  7
#define PIN_D6  8
#define PIN_D7  9

#define LCD_INTENSITY 135


#define PIXEL_DISTANCE  10      // virtual distance between pixels

class Display
{
    LedControl lc = LedControl(PIN_DIN, PIN_CLK, PIN_LOAD, 1);
    LiquidCrystal lcd = LiquidCrystal(PIN_RS, PIN_E, PIN_D4, PIN_D5, PIN_D6, PIN_D7);

    bool flipped;

    static Display* instance;
    Display();
    
public:
    static Display* getInstance();

    void setPixel(byte row, byte col, bool state);
    void setCol(byte col, byte value);
    void setRow(byte row, byte value);
    void flip();
    void clear();
    void printOnLcd(byte row, const char *msg, byte col = 0);
    void clearLcd();
};

#endif