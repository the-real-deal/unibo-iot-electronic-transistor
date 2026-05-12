#include "SweepingTask.hpp"
#include "model/messageManager/Logger.h"

#define DELTA 5

SweepingTask::SweepingTask(ServoMotorImpl *_servo, Context *context, bool forward, ContextType destCtx) : servo(_servo),
                                                                                                          ctx(context),
                                                                                                          destContext(destCtx)
{
    // this->stateTimestamp = millis();
    // this->sweepConstant = forward ? 0 : 180;
    this->sweepSign = forward ? -1 : 1;
    this->destination = forward ? 180 : 0;
    this->hasJustEntered = true;
    this->servo->on();
}

void SweepingTask::cleanup()
{
}

void SweepingTask::execute()
{
    if (this->hasJustEntered)
    {
        this->hasJustEntered = false;
        this->servo->setPosition(destination);
    }
    else if (this->destination + this->sweepSign * this->servo->getPosition() <= DELTA)
    {
        this->servo->off();
        this->setCompleted();
        this->ctx->checkUpdate(this->destContext);
    }
    /* Old implementation */
    // long dt = elapsedSweepingTime();
    // /* if forward sweep -> 0 + ... ; if backwards sweep -> 180 - ... */
    // currentPos = this->sweepConstant + this->sweepSign * (((float)dt) / SWEEP_TIME) * 180;
    // servo->setPosition(currentPos);

    // if (currentPos == (180 - sweepConstant))
    // {
    //     this->setCompleted();
    //     this->ctx->checkUpdate(this->destContext);
    // }
}

long SweepingTask::elapsedSweepingTime()
{
    return 0;
    // return millis() - stateTimestamp;
}