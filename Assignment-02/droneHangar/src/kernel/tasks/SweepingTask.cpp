#include "SweepingTask.hpp"
#include "model/messageManager/Logger.h"

#define DELTA 5

SweepingTask::SweepingTask(ServoMotorImpl *_servo, Context *context, bool forward, ContextType destCtx) : servo(_servo),
                                                                                                          ctx(context),
                                                                                                          destContext(destCtx)
{
    this->sweepSign = forward ? -1 : 1;
    this->destination = forward ? 180 : 0;
    this->hasJustEntered = true;
}

void SweepingTask::cleanup()
{
}

void SweepingTask::execute()
{
    if (this->hasJustEntered)
    {
        this->hasJustEntered = false;
        // this->servo->on();
        this->servo->setPosition(destination);
    }
    else if (this->destination + this->sweepSign * this->servo->getPosition() <= DELTA)
    {
        // this->servo->off();
        this->setCompleted();
        this->ctx->checkUpdate(this->destContext);
    }
}
