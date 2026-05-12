#include "LedBlinkTask.hpp"
#include "Arduino.h"
#include "model/messageManager/Logger.h"

LedBlinkTask::LedBlinkTask(Led *led) : led(led) {}

LedBlinkTask::~LedBlinkTask()
{
    cleanup();
}

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