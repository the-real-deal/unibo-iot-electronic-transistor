#include "LedBlinkTask.hpp"
#include "Arduino.h"
#include "model/messageManager/Logger.h"

LedBlinkTask::LedBlinkTask(Led *led) : led(led) {}

void LedBlinkTask::cleanup()
{
    this->led->switchOff();
}

void LedBlinkTask::execute()
{
    if (this->led->isOn())
    {
        this->led->switchOff();
    }
    else
    {
        this->led->switchOn();
    }
}