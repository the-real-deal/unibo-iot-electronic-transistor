#include "ReadTempTask.hpp"

ReadTempTask::ReadTempTask(TempSensor *tempSensor, Context *ctx, InputHolder *holder, ContextType destCtx) : 
    tempSensor(tempSensor),
    context(ctx),
    holder(holder),
    destCtx(destCtx) {}

void ReadTempTask::cleanup()
{
}

void ReadTempTask::execute()
{
    float temp = this->tempSensor->getTemperature();
    this->holder->setTemperature(temp);
    this->context->checkUpdate(destCtx);
}
