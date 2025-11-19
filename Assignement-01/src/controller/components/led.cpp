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

void ledFading(int ledPin, int &brightness, short &direction, bool reset)
{
    if (reset)
        brightness = 0;
    else
        brightness += direction;

    if (brightness < 0 || brightness > 255)
    {
        direction = -direction;
        brightness += direction;
    }

    analogWrite(ledPin, brightness);
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