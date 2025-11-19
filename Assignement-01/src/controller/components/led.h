#ifndef LED_H
#define LED_H
#include "config.h"

void resetLed(int *ledPins, bool *ledsOn, int length);

void ledFading(int ledPin, int &counter, short &direction, bool reset);

int LedShow(int *ledPins, int *answer, int length);
#endif