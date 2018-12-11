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
}

void setup()
{
    d = Display::getInstance();

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    Serial.begin(9600);

    delay(1000);
}

void loop() 
{
    displayTest();
    // b.updatePosition();
}