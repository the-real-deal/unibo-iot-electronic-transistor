#include "button.h"
#include "../../config.h"
#include <Arduino.h>

long prevts[CODE_LENGTH] = {0, 0, 0, 0};

bool button_no_bouncing(int i)
{
    long ts = millis();
    if (ts - prevts[i] > DEBOUNCE_TIME)
    {
        prevts[i] = ts;
        return true;
    }
    return false;
}
