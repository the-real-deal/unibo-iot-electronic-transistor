#include "ReadDistanceTask.hpp"

ReadDistanceTask::ReadDistanceTask(ProximitySensor *sonar, Context* ctx, InputHolder *valHolder, ContextType type):
    sonar(sonar),
    context(ctx),
    holder(valHolder),
    destCtx(type) {}

void ReadDistanceTask::cleanup()
{
}

void ReadDistanceTask::execute()
{
    float dist = this->sonar->getDistance();
    this->holder->setDistance(dist);
    this->context->checkUpdate(this->destCtx);
}
