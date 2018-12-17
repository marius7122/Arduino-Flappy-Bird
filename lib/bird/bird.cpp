#include "bird.h"
#include "pipe.h"

Bird::Bird()
{
    birdLedY = START_LED_Y;
    posY = START_LED_Y * PIXEL_DISTANCE;
    lastUpdate = 0;
    velocity = 0;
    display = Display::getInstance();
    dead = false;
}

void Bird::updatePosition()
{
    if(dead)
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

    if(PipeManager::getPosition(birdLedY, POS_X) == true)
    {
        dead = true;
        // Serial.println("DEAD!!");
    }
    
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

void Bird::searchColision()
{
    
    // if the bird hit a pipe
    if(PipeManager::getPosition(birdLedY, POS_X) == true)
    {
        dead = true;
        // Serial.println("DEAD!!");
    }
}

bool Bird::isDead()
{
    return dead;
}