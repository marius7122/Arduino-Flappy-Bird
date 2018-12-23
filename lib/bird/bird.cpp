#include "bird.h"
#include "pipe.h"

Bird::Bird()
{
    initialize();
}

void Bird::initialize()
{
    birdLedY = START_LED_Y;
    posY = START_LED_Y * PIXEL_DISTANCE;
    lastUpdate = millis();
    velocity = 0;
    display = Display::getInstance();
    dead = false;
    inactive = true;
    PipeManager::setBirdPosition(POS_X, birdLedY);
}

void Bird::updatePosition()
{
    if(dead)
        return;
    if(inactive)
        return;

    unsigned long currentTime = millis();
    unsigned long deltaTime = currentTime - lastUpdate;

    velocity -= deltaTime * 0.001 * GRAVITY;
    if(velocity > 0 && velocity < MIN_SPEED)
        velocity = -MIN_SPEED;

    posY += deltaTime * 0.001 * velocity;

    if(posY < 0)
    {
        dead = true;
        return;
    }

    posY = min(7.5 * PIXEL_DISTANCE, posY);

    int newLedY = (int)(posY / PIXEL_DISTANCE);
    if(newLedY != birdLedY)
        moveBird(newLedY);

    searchColision();
    
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
    PipeManager::setBirdPosition(POS_X, birdLedY);
    display->setPixel(birdLedY, POS_X, true);
}

void Bird::jump()
{
    velocity = JUMP_VELOCITY;
    updatePosition();
}

void Bird::searchColision()
{
    
    // if the bird hit a pipe
    if(PipeManager::getPosition(birdLedY, POS_X) == true)
    {
        dead = true;
    }
}

bool Bird::isDead()
{
    return dead;
}

void Bird::startMove()
{
    lastUpdate = millis();
    inactive = false;
}

void Bird::reset()
{
    display->setPixel(birdLedY, POS_X, false);
    initialize();
}