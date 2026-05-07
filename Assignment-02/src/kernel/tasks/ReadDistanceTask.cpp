#include "ReadDistanceTask.hpp"
#include "model/messageManager/Logger.h"

ReadDistanceTask::ReadDistanceTask(ProximitySensor *sonar, Context *ctx, InputHolder *valHolder, ContextType type) : sonar(sonar),
                                                                                                                     context(ctx),
                                                                                                                     holder(valHolder),
                                                                                                                     destCtx(type) {}

void ReadDistanceTask::cleanup()
{
    this->holder->setDistance(0.0);
}

void ReadDistanceTask::execute()
{
    float dist = this->sonar->getDistance();
    // Logger.log(String(dist));
    this->holder->setDistance(dist);
    this->context->checkUpdate(this->destCtx);
}
