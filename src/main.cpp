#include <Arduino.h>
#include "display.h"
#include "bird.h"
#include "pipe.h"

#define BUTTON_PIN 2

Display *d;
// Bird b;

void displayTest()
{
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
            d->setPixel(i, j, 1);
            delay(50);
            d->setPixel(i, j, 0);
        }
    
    for(int i=0; i<8; i++)
    {
        d->setCol(i, B11111111);
        delay(100);
        d->setCol(i, B00000000);        
    }

    for(int i=0; i<8; i++)
    {
        d->setRow(i, B11111111); 
        delay(100);
        d->setRow(i, B00000000); 
    }
}

void setup()
{
    d = Display::getInstance();
    d->flip();

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    Serial.begin(9600);

    d->setCol(1, B01000001);
}

void loop() 
{
    // displayTest();
    // b.updatePosition();
}