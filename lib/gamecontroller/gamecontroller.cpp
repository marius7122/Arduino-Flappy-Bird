#include "gamecontroller.h"
#include <EEPROM.h>

#define HIGHSCORE_ADRESS 128

GameController::GameController()
{
    initialize();
}

void GameController::initialize()
{
    score = 0;
    gameOver = false;
    gameStarted = false;
    display = Display::getInstance();

    pinMode(JUMP_BUTTON_PIN, INPUT_PULLUP);

    // Serial.println("Press a button to start the game!");
    display->clearLcd();
    display->printOnLcd(0, "Press a button!");

    byte highscore = EEPROM.read(HIGHSCORE_ADRESS);
    char buffer[10];
    itoa(highscore, buffer, 10);
    display->printOnLcd(1, "Highscore:");
    display->printOnLcd(1, buffer, 12);
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
        display->clearLcd();
        display->printOnLcd(0, "Gameover!");
        display->printOnLcd(1, "Score: ");
        score = pipe.getScore();
        char buffer[10];
        itoa(score, buffer, 10);
        display->printOnLcd(1, buffer, 10);

        byte highscore = EEPROM.read(HIGHSCORE_ADRESS);
        if(score > highscore)
            EEPROM.write(HIGHSCORE_ADRESS, score);

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
    
    // Serial.println("Game started!");
}

void GameController::restart()
{
    // Serial.println("Game restart!");

    bird.reset();
    pipe.restart();
    initialize();
    delay(500);
}