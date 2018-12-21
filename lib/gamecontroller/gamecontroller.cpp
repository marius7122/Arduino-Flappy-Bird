#include "gamecontroller.h"
#include <EEPROM.h>

#define HIGHSCORE_ADRESS 128

GameController::GameController()
{
    initialize();
}

void GameController::initialize()
{
    display->clear();

    score = 0;
    gameOver = false;
    gameStarted = false;
    display = Display::getInstance();
    lastScoreUpdate = 0;

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

    // Game Over
    if(bird.isDead())
    {
        gameOver = true;
        score = pipe.getScore();
        byte highscore = EEPROM.read(HIGHSCORE_ADRESS);
        
        // display message on LCD
        display->clearLcd();
        if(score > highscore)
        {
            EEPROM.write(HIGHSCORE_ADRESS, score);
            display->printOnLcd(0, "New Highscore!");
        }
        else
        {
            display->printOnLcd(0, "Game Over!");
        }

        display->printOnLcd(1, "Score: ");
        char buffer[10];
        itoa(score, buffer, 10);
        display->printOnLcd(1, buffer, 10);

        fadeOut();

        return;
    }

    pipe.updatePosition();
    if(!pipe.onDisplay())
        pipe.reset();
    
    // update LCD score every 500 ms
    if(millis() - lastScoreUpdate > 500)
    {   
        display->clearLcd();
        score = pipe.getScore();
        char buffer[10];
        itoa(score, buffer, 10);
        display->printOnLcd(0, "Score:");
        display->printOnLcd(0, buffer, 10);
        lastScoreUpdate = millis();
    }
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

void GameController::fadeOut()
{
    byte posX[64], posY[64];
    byte sz = 0, line, col;

    // search for inactive pixels
    for(line = 0; line < 8; line++)
        for(col = 0; col < 8; col++)
            if(!PipeManager::getPosition(line, col))
            {
                posX[sz] = col;
                posY[sz] = line;
                sz++;
            }
    
    // shuffle
    byte i, j, aux;
    for(i = 0; i < sz; i++)
    {
        j = random(0, sz);

        aux = posX[i];
        posX[i] = posX[j];
        posX[j] = aux;
        
        aux = posY[i];
        posY[i] = posY[j];
        posY[j] = aux;
    }

    for(i = 0; i < sz; i++)
    {
        display->setPixel(posY[i], posX[i], true);
        delay(30);
    }
}

void GameController::resetHighscore()
{
    EEPROM.write(HIGHSCORE_ADRESS, 0);
}