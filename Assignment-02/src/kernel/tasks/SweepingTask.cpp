#include "SweepingTask.hpp"
#include "Arduino.h"
#include "config.h"

SweepingTask::SweepingTask(ServoMotor *_servo, bool forward) : servo(_servo)
{
    this->stateTimestamp = millis();
    this->sweepConstant = forward ? 0 : 180;
    this->sweepSign = forward ? 1 : -1;
}

void SweepingTask::cleanup()
{
}

void SweepingTask::execute()
{
    long dt = elapsedSweepingTime();
    /* if forward sweep -> 0 + ... ; if backwards sweep -> 180 - ... */
    currentPos = this->sweepConstant + this->sweepSign * (((float) dt)/SWEEP_TIME)*180;
    servo->setPosition(currentPos);

    if(currentPos == (180 - sweepConstant))
    {
        this->setCompleted();
    }
}

long SweepingTask::elapsedSweepingTime()
{
    return millis() - stateTimestamp;
}