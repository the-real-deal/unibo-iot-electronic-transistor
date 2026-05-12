#include "ReadTempTask.hpp"
#include "model/messageManager/Logger.h"

ReadTempTask::ReadTempTask(TempSensor *tempSensor, Context *ctx, InputHolder *holder, ContextType destCtx) : tempSensor(tempSensor),
                                                                                                             context(ctx),
                                                                                                             holder(holder),
                                                                                                             destCtx(destCtx)
{
}

ReadTempTask::~ReadTempTask()
{
    cleanup();
}

void ReadTempTask::cleanup()
{
    // this->holder->setTemperature(Temp1 - 1.0);
}

void ReadTempTask::execute()
{
    float temp = this->tempSensor->getTemperature();
    this->holder->setTemperature(temp);
    Logger.log(String(holder->getTemperature()));
    this->context->checkUpdate(destCtx);
}
