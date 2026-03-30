#include "ReadSonarTask.hpp"

ReadSonarTask::ReadSonarTask(Sonar *sonar, Context* ctx, InputHolder *valHolder) : sonar(sonar), context(ctx), holder(valHolder)
{
}

void ReadSonarTask::cleanup()
{
}

void ReadSonarTask::execute()
{
    float dist = sonar->getDistance();
    holder->setDistance(dist);
    // context check values
}
