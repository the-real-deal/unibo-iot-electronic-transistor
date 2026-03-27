#include "LedBlinkTask.hpp"
#include "Arduino.h"

LedBlinkTask::LedBlinkTask(Led *led) : led(led) {}

void LedBlinkTask::cleanup()
{
    led->switchOff();
}

void LedBlinkTask::execute()
{
    if (led->isOn())
    {
        led->switchOff();
    }
    else
    {
        led->switchOn();
    }
}