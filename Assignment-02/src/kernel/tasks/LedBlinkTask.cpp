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
    led->switchOn();
    // setCompleted();
}