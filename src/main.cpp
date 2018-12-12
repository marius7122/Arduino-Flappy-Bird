#include <Arduino.h>
#include "display.h"
// #include "bird.h"
// #include "pipe.h"
#include "gamecontroller.h"


Display *display;

GameController game;

void displayTest()
{
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
            display->setPixel(i, j, 1);
            delay(50);
            display->setPixel(i, j, 0);
        }
    
    for(int i=0; i<8; i++)
    {
        display->setCol(i, B11111111);
        delay(100);
        display->setCol(i, B00000000);        
    }

    for(int i=0; i<8; i++)
    {
        display->setRow(i, B11111111); 
        delay(100);
        display->setRow(i, B00000000); 
    }
}

void setup()
{
    display = Display::getInstance();

    Serial.begin(9600);
}

void loop() 
{
    game.updateFrame();
}