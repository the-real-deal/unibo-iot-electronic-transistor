#include "ReadPIRTask.hpp"

ReadPIRTask::ReadPIRTask(Pir *pir, Context *ctx, InputHolder *holder, ContextType destCtx): 
    pir(pir), 
    context(ctx), 
    holder(holder),
    destCtx(destCtx) {}

void ReadPIRTask::cleanup()
{
}

void ReadPIRTask::execute()
{
    bool isDetected = this->pir->isDetected();
    this->holder->setMotionDetected(isDetected);
    this->context->checkUpdate(destCtx);
}
