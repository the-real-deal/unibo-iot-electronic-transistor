#ifndef LED_H
#define LED_H
#include "config.h"

/*
 * Function to reset all LEDs to off state
 * Parameters:
 *  - int *ledPins: array of LED pin numbers
 *  - bool *ledsOn: array of LED states to update
 *  - int length: number of LEDs
 */
void resetLed(int *ledPins, bool *ledsOn, int length);

/*
 * Function to create a fading effect on an LED
 * Parameters:
 *  - int ledPin: pin number of the LED
 *  - int &brightness: reference to the led brightness
 *  - short &direction: reference to the direction of fading (increasing or decreasing)
 *  - bool reset: flag to reset the brightness.
 */
void ledFading(int ledPin, int &brightness, short &direction, bool reset);

/*
 * Function to display a sequence on LEDs
 * Parameters:
 *  - int *ledPins: array of LED pin numbers
 *  - int *answer: array representing the sequence to display
 *  - int length: length of the sequence
 * Returns:
 *  - int: total delay time used to display the sequence
 */
int LedShow(int *ledPins, int *answer, int length);

#endif