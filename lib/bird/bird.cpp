#include "bird.h"

Bird::Bird()
{
    birdLedY = START_LED_Y;
    posY = START_LED_Y * PIXEL_DISTANCE;
    lastUpdate = 0;
    velocity = 0;
    display = Display::getInstance();
    
    Serial.begin(9600);
}

void Bird::updatePosition()
{
    unsigned long currentTime = millis();
    unsigned long deltaTime = currentTime - lastUpdate;
    
    velocity -= deltaTime * 0.001 * GRAVITY;
    if(velocity > 0 && velocity < MIN_SPEED)
        velocity = -MIN_SPEED;

    posY += deltaTime * 0.001 * velocity;

    posY = max(0, posY);
    posY = min(7.5 * PIXEL_DISTANCE, posY);

    int newLedY = (int)(posY / PIXEL_DISTANCE);
    if(newLedY != birdLedY)
        moveBird(newLedY);
    
    lastUpdate = currentTime;
}

void Bird::moveBird(int newLedY)
{
    // turn off old position
    display->setPixel(birdLedY, POS_X, false);

    birdLedY = newLedY;

    // draw new position
    drawBird();
}

void Bird::drawBird()
{
    display->setPixel(birdLedY, POS_X, true);
}

void Bird::jump()
{
    velocity = JUMP_VELOCITY;
    updatePosition();
}