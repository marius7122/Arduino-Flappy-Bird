#include "gamecontroller.h"

GameController::GameController()
{
    initialize();
}

void GameController::initialize()
{
    score = 0;
    gameOver = false;
    gameStarted = false;

    pinMode(JUMP_BUTTON_PIN, INPUT_PULLUP);

    Serial.println("Press a button to start the game!");
}

void GameController::updateFrame()
{
    // start the game
    if(!gameStarted && !digitalRead(JUMP_BUTTON_PIN))
       startGame();

    // game not started
    if(!gameStarted)
       return;

    // restart the game
    if(gameOver && !digitalRead(JUMP_BUTTON_PIN))
        restart();

    // game over
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
    gameStarted = true;
    pipe.startMove();
    bird.startMove();
    delay(100);
    
    Serial.println("Game started!");
}

void GameController::restart()
{
    Serial.println("Game restart!");

    bird.reset();
    pipe.restart();
    initialize();
    delay(500);
}