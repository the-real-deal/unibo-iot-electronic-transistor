#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include "../model/TournOnSequence.h"

void control();

/*
 * Function that initializes the LCD screen
 */
void setupLcd();

/*
 * Function that initializes the game model
 */
void gameModel();

/*
 * Function that handles button presses with debounce
 * i: index of the button
 * action: function to be called when the button is pressed
 */
bool button_no_bouncing(int i); // , void (*action)()

/*
 * Action to be performed when a game button is pressed
 * i: index of the button pressed
 */
void gameButtonPressed(int i);

/*
 * Function called in the main loop to handle the MENU state
 */
void gameMenu();

/*
 * Function called in the main loop to handle the PLAYING state
 */
void gamePlaying();

/*
 * Function called in the main loop to handle the WIN state
 */
void gameWin();

/*
 * Function called in the main loop to handle the GAMEOVER state
 */
void gameLoss();

/*
 * Function that enables interrupts for BUTTON_PIN_1
 */
void interruptButton1();

/*
 * Function that enables interrupts for the buttons [BUTTON_PIN_2, BUTTON_PIN_3, BUTTON_PIN_4]
 */
void enableInterruptGameButtons();

/*
 * Function that puts the microcontroller to sleep
 */
void sleep();

void resetAllLed();
#endif