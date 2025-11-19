#define EI_ARDUINO_INTERRUPTED_PIN
#include <EnableInterrupt.h>
#include <avr/sleep.h>
#include <math.h>
#include <Arduino.h>
#include <string.h>
#include "systemController.h"
#include "../config.h"
#include "./components/led.h"
#include "./components/button.h"
#include "./components/lcd.h"
#include "../utils.h"

int buttonPins[CODE_LENGTH] = {BUTTON_PIN_1, BUTTON_PIN_2, BUTTON_PIN_3, BUTTON_PIN_4};
int ledPins[CODE_LENGTH] = {LED_PIN_1, LED_PIN_2, LED_PIN_3, LED_PIN_4};
bool ledsOn[CODE_LENGTH] = {false, false, false, false};

int counter = 0;
short direction = FADING_STEP;

bool stateJustChanged = true;
unsigned long nowTime;
Game g;

void control()
{
    switch (g.state)
    {
    case GameState::MENU:
        gameMenu();
        break;
    case GameState::GAME:
        gamePlaying();
        break;
    case GameState::GAMEOVER:
        gameLoss();
        break;
    case GameState::WIN:
        gameWin();
        break;
    case GameState::SLEEP:
        sleep();
        break;
    }
}

void gameModel()
{
    g = setupGame(analogRead(1));
}

void gameMenu()
{
    if (stateJustChanged)
    {
        nowTime = millis();
        resetAllLed();
        stateJustChanged = false;
        printToLcd(2, "Welcome to TOS!", "Press B1 2 Start!");
    }
    if (millis() - nowTime > SLEEP_TIME)
    {
        g.state = GameState::SLEEP;
    }

    ledFading(RED_LED, counter, direction, false);

    int diff = round((MAX_DIFF_VAL / MAX_READ_VAL) * analogRead(ANALOG0)) + 1;
    Difficulty difficulty = static_cast<Difficulty>(diff);

    if (difficulty != g.difficulty)
    {
        changeDifficulty(g, difficulty);
        char diffStr[10] = "Diff: ";
        sprintf(diffStr + 6, "%d", static_cast<int>(difficulty));
        printToLcd(2, "Press B1 2 Start!", diffStr);
    }
}

void gameButtonPressed(int i)
{
    ledsOn[i] = true;
    addDigit(g, i + 1);
}

void resetAllLed()
{
    resetLed(ledPins, ledsOn, CODE_LENGTH);
    ledFading(RED_LED, counter, direction, true);
}

void gamePlaying()
{
    if (stateJustChanged)
    {
        nowTime = millis();
        stateJustChanged = false;
        resetAllLed();
        generateCode(g);
        printToLcd(1, "GO!");
        delay(1000);
        char buff[5];
        sprintf(buff, "%d%d%d%d", g.code[0], g.code[1], g.code[2], g.code[3]);
        printToLcd(1, buff);
    }
    if (millis() - nowTime > g.maxTime)
    {
        g.state = GameState::GAMEOVER;
    }
    else
    {
        for (int i = 0; i < CODE_LENGTH; i++)
        {
            digitalWrite(ledPins[i], ledsOn[i] ? HIGH : LOW);
        }

        if (g.answerLength == 4)
        {
            if (checkAnswer(g))
            {
                g.state = GameState::WIN;
            }
            else
            {
                g.state = GameState::GAMEOVER;
            }
        }
    }
}

void gameLoss()
{
    resetAllLed();
    digitalWrite(RED_LED, HIGH);

    char *buff = new char[(int)floor(log10(g.score)) + 1];
    sprintf(buff, "Final Score: %d", g.score);
    printToLcd(2, "Game Over", buff);
    delete buff;

    delay(2000);
    digitalWrite(RED_LED, LOW);
    delay(6000);
    stateJustChanged = true;
    reset(g);
}

void gameWin()
{
    g.score++;
    reduceTime(g);
    char *scoreBuff = new char[(int)floor(log10(g.score)) + 1];
    sprintf(scoreBuff, "GOOD! Score: %d", g.score);
    printToLcd(1, scoreBuff);
    delete scoreBuff;
    int tmp = LedShow(ledPins, g.answer, CODE_LENGTH);
    delay(max(0, 5000 - tmp));
    stateJustChanged = true;
    g.state = GameState::GAME;
}

void sleep()
{
    resetAllLed();
    printToLcd(2, "Sleeping...", "Press B1 to Wake");
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    sleep_enable();

    for (int i = 0; i < CODE_LENGTH; i++)
    {
        disableInterrupt(ledPins[i]);
    }

    sleep_mode();

    enableInterruptGameButtons();
}

void interruptButton1()
{
    enableInterrupt(buttonPins[0], []()
                    {
        if(button_no_bouncing(0))
        {

            switch(g.state)                            
            {
                case GameState::MENU:
                    g.state = GameState::GAME;
                    ledFading(RED_LED, counter, direction,  true);
                    stateJustChanged = true;
                    break;
                case GameState::GAME:
                    gameButtonPressed(0);
                    break;
                case GameState::SLEEP:
                    stateJustChanged = true;
                    g.state = GameState::MENU;
                    break;
                case GameState::GAMEOVER:
                    break;
                case GameState::WIN:
                    break;
            }
        }; }, RISING);
}

void enableInterruptGameButtons()
{
    for (int i = 1; i < CODE_LENGTH; i++)
    {
        enableInterrupt(buttonPins[i], []()
                        {
            int indexButton = indexof(arduinoInterruptedPin, buttonPins, CODE_LENGTH);
            if(indexButton > 0)
            {
                if(button_no_bouncing(indexButton) && g.state == GameState::GAME)
                    gameButtonPressed(indexButton);
            } }, RISING);
    }
}
