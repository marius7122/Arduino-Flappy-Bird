#include <Arduino.h>
#include "display.h"
#include "bird.h"

#define BUTTON_PIN 2


Display *d;
Bird bird;

void setup()
{
    d = Display::getInstance();
    d->rotate90();

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    Serial.begin(9600);

    delay(1000);
}

void loop() 
{
    bird.updatePosition();

    if(digitalRead(BUTTON_PIN) == LOW)
        bird.jump();

    delay(50);
}