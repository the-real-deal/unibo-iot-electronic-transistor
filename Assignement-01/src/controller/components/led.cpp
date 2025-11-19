#include "led.h"
#include <Arduino.h>

#define FADING_STEP 10

void resetLed(int *ledPins, bool *ledsOn, int length)
{
    for (int i = 0; i < length; i++)
    {
        ledsOn[i] = false;
        digitalWrite(ledPins[i], ledsOn[i] ? HIGH : LOW);
    }
}

void ledFading(int ledPin, int &counter, short &direction, bool reset)
{
    if (reset)
        counter = 0;
    else
        counter += direction;

    if (counter < 0 || counter > 255)
    {
        direction = -direction;
        counter += direction;
    }

    analogWrite(ledPin, counter);
}

int LedShow(int *ledPins, int *answer, int length)
{
    int delayReturned = 0;
    const int delayPerLed = 500;
    for (int i = length - 1; i >= 0; i--)
    {
        delay(delayPerLed);
        delayReturned += delayPerLed;
        digitalWrite(ledPins[answer[i] - 1], LOW);
    }
    return delayReturned;
}