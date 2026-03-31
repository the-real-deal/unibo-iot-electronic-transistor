#include "Arduino.h"
#include "Timer.hpp"

void Timer::init()
{
    this->startTime = millis();
}

bool Timer::hasExeeded(int sec)
{
    return millis() - this->startTime > sec * 1000;
}

void Timer::reset()
{
    this->init();
}