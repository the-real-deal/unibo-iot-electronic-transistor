#include "LedBlinkTask.hpp"
#include "Arduino.h"

LedBlinkTask::~LedBlinkTask()
{
}

void LedBlinkTask::init()
{
    Task::init();
}

void LedBlinkTask::tick()
{
    led.switchOn();
    delay(100);
    led.setIntensity(intensity);
    delay(100);
    setCompleted();
}