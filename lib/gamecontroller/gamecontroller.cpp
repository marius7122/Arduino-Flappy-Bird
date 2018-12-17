#include "gamecontroller.h"

GameController::GameController()
{
    score = 0;
    gameOver = false;
    gameStarted = false;

    pinMode(JUMP_BUTTON_PIN, INPUT_PULLUP);

    Serial.println("Press a button to start the game!");
}

void GameController::updateFrame()
{
    if(!gameStarted && !digitalRead(JUMP_BUTTON_PIN))
       startGame();

    if(!gameStarted)
       return;

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

void GameController::startGame()
{
    delay(100);

    gameStarted = true;
    pipe.startMove();
    bird.startMove();
    
    Serial.println("Game started!");
}