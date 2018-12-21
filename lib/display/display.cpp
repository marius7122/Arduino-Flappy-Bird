#include "display.h"

Display* Display::instance = nullptr;

Display::Display()
{
    // led matrix init
    lc.shutdown(0, false);
    lc.setIntensity(0, INTENSITY);
    lc.clearDisplay(0);
    flipped = true;     // by default display is flipped

    // lcd init
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(2, 1);

    lcd.print("HELLO WORLD!");

    pinMode(PIN_V0, OUTPUT);
    analogWrite(PIN_V0, LCD_INTENSITY);
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

void Display::clear()
{
    byte line, col;
    for(line = 0; line < 8; line++)
        for(col = 0; col < 8; col++)
            setPixel(line, col, false);
}

void Display::printOnLcd(byte row, const char *msg, byte col = 0)
{
    lcd.setCursor(col, row);
    lcd.print(msg);
}

void Display::clearLcd()
{
    lcd.clear();
}