#include "LedBlinkTask.hpp"
#include "Arduino.h"
#include "model/messageManager/Logger.h"

LedBlinkTask::LedBlinkTask(Led *led) : led(led) {}

void LedBlinkTask::cleanup()
{
    led->switchOff();
}

void LedBlinkTask::execute()
{
    Logger.log("Blinking");
    if (led->isOn())
    {
        led->switchOff();
    }
    else
    {
        led->switchOn();
    }
}