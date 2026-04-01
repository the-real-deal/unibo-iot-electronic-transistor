#include "ReadSonarTask.hpp"

ReadSonarTask::ReadSonarTask(Sonar *sonar, Context* ctx, InputHolder *valHolder, ContextType type):
    sonar(sonar),
    context(ctx),
    holder(valHolder),
    destCtx(type) {}

void ReadSonarTask::cleanup()
{
}

void ReadSonarTask::execute()
{
    float dist = this->sonar->getDistance();
    this->holder->setDistance(dist);
    this->context->checkUpdate(this->destCtx);
}
