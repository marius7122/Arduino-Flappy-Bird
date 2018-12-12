#include "gamecontroller.h"

GameController::GameController()
{
    score = 0;
    gameOver = false;

    pinMode(JUMP_BUTTON_PIN, INPUT_PULLUP);
}

void GameController::updateFrame()
{
    if(gameOver)
        return;

    if(!digitalRead(JUMP_BUTTON_PIN) && millis() - lastJump >= JUMP_TIME)
    {
        bird.jump();
        lastJump = millis();
    }
    bird.updatePosition();

    if(bird.isDead())
    {
        gameOver = true;
        Serial.println("GAMEOVER!");
        return;
    }

    pipe.updatePosition();
    if(!pipe.onDisplay())
        pipe.reset();
}