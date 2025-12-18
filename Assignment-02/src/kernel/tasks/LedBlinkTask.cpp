#include "LedBlinkTask.hpp"
#include "Arduino.h"

LedBlinkTask::~LedBlinkTask()
{
}

void LedBlinkTask::cleanup()
{
}

void LedBlinkTask::excecute()
{
    if (!ledIsOn)
    {
        led->switchOn();
        ledIsOn = true;
        // setCompleted();
    }
    else
    {
        led->switchOff();
        ledIsOn = false;
    }
}