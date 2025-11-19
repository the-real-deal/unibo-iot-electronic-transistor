#define EI_ARDUINO_INTERRUPTED_PIN
#include <EnableInterrupt.h>
#include <LiquidCrystal_I2C.h>
#include <avr/sleep.h>
#include <math.h>
#include <Arduino.h>
#include "systemController.h"
#include "../config.h"

void resetLed();
int indexof(int value, int *array, int length);
LiquidCrystal_I2C lcd(0x27, 20, 4);
int buttonPins[CODE_LENGTH] = {BUTTON_PIN_1, BUTTON_PIN_2, BUTTON_PIN_3, BUTTON_PIN_4};
int ledPins[CODE_LENGTH] = {LED_PIN_1, LED_PIN_2, LED_PIN_3, LED_PIN_4};
bool ledsOn[CODE_LENGTH] = {false, false, false, false};
long prevts[CODE_LENGTH] = {0, 0, 0, 0};

int counter = 0;
short direction = 10;
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

bool button_no_bouncing(int i) // , void (*action)()
{
    long ts = millis();
    if (ts - prevts[i] > DEBOUNCE_TIME)
    {
        prevts[i] = ts;
        return true;
        // action();
    }
    return false;
}

void setupLcd()
{
    lcd.init();
    lcd.backlight();
}

void gameModel()
{
    g = setupGame();
}

void gameMenu()
{
    if (stateJustChanged)
    {
        nowTime = millis();
        stateJustChanged = false;
        lcd.setCursor(0, 0);
        lcd.print("Welcome to TOS!");
        lcd.setCursor(0, 1);
        lcd.print("Press B1 to Start!");
    }
    if (millis() - nowTime > 10000)
    {
        g.state = GameState::SLEEP;
    }

    analogWrite(RED_LED, counter);

    counter += direction;
    if (counter > 255 || counter < 0)
    {
        direction = -direction;
        counter += direction;
    }
    // read the input on analog pin 0 and map it to a range from 1 to 3;
    Difficulty difficulty = static_cast<Difficulty>(round((MAX_DIFF_VAL / MAX_READ_VAL) * analogRead(A0)) + 1);

    changeDifficulty(g, difficulty);
}

void gameButtonPressed(int i)
{
    ledsOn[i] = true;
    addDigit(g, i + 1);
}

void gamePlaying()
{
    if (stateJustChanged)
    {
        nowTime = millis();
        stateJustChanged = false;
        resetLed();
        generateCode(g);
        lcd.setCursor(0, 0);
        lcd.clear();
        lcd.print("GO!");
        delay(1000);
        lcd.clear();
        char buff[5];
        sprintf(buff, "%d%d%d%d", g.code[0], g.code[1], g.code[2], g.code[3]);
        lcd.print(buff);
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
    resetLed();
    digitalWrite(RED_LED, HIGH);
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("Game Over");
    lcd.setCursor(0, 1);
    lcd.print("Final Score ");
    lcd.print(g.score);
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
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("GOOD! Score:");
    lcd.print(g.score);
    delay(5000);
    stateJustChanged = true;
    g.state = GameState::GAME;
}

void resetLed()
{
    for (int i = 0; i < CODE_LENGTH; i++)
    {
        ledsOn[i] = false;
        digitalWrite(ledPins[i], ledsOn[i] ? HIGH : LOW);
    }

    counter = 0;
    analogWrite(RED_LED, counter);
}

void sleep()
{
    resetLed();

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    sleep_enable();

    disableInterrupt(ledPins[0]);
    disableInterrupt(ledPins[1]);
    disableInterrupt(ledPins[2]);

    sleep_mode();

    interruptGameButtons();
}

void interruptButton1()
{
    enableInterrupt(buttonPins[0], []()
                    {
            if(button_no_bouncing(0)){

                switch(g.state)                            
                {
                    case GameState::MENU:
                        g.state = GameState::GAME;
                        counter = 0;
                        analogWrite(RED_LED, counter);
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

void interruptGameButtons()
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

int indexof(int value, int *array, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (array[i] == value)
            return i;
    }
    return -1;
}