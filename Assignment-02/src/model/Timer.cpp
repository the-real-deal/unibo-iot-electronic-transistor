#include "Arduino.h"
#include "Timer.hpp"

void Timer::init()
{
    this->startTime = millis();
    this->stopInit = 0;
    this->elapsedInterruption = 0;
    this->isStopped = false;
    this->isReset = false;
}

bool Timer::hasExeeded(unsigned int sec)
{
    return (millis() - this->startTime) - elapsedInterruption > sec * 1000U;
}

void Timer::reset()
{
    this->isReset = true;
}

void Timer::stop()
{
    if(!this->isStopped && !this->isReset)
    {
        this->stopInit = millis();
        this->isStopped = true;
    }
}

void Timer::resume()
{
    if(this->isStopped && !this->isReset)
    {
        this->elapsedInterruption += millis() - this->stopInit;
        this->isStopped = false;
    }
}

bool Timer::isRunning()
{
    return !this->isReset;
}