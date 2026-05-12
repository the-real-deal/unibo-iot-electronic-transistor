#include "ReadPIRTask.hpp"
#include "model/messageManager/Logger.h"

ReadPIRTask::ReadPIRTask(Pir *pir, Context *ctx, InputHolder *holder, ContextType destCtx) : pir(pir),
                                                                                             context(ctx),
                                                                                             holder(holder),
                                                                                             destCtx(destCtx) {}

ReadPIRTask::~ReadPIRTask()
{
    cleanup();
}

void ReadPIRTask::cleanup()
{
    // this->holder->setMotionDetected(false);
}

void ReadPIRTask::execute()
{
    this->pir->sync();
    bool isDetected = this->pir->isDetected();
    // Logger.log(String(isDetected));
    this->holder->setMotionDetected(isDetected);
    this->context->checkUpdate(destCtx);
}
