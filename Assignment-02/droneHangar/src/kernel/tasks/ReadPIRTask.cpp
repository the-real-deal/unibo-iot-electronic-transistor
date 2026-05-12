#include "ReadPIRTask.hpp"
#include "model/messageManager/Logger.h"

ReadPIRTask::ReadPIRTask(Pir *pir, Context *ctx, InputHolder *holder, ContextType destCtx) : pir(pir),
                                                                                             context(ctx),
                                                                                             holder(holder),
                                                                                             destCtx(destCtx) {}

void ReadPIRTask::cleanup()
{
    // this->holder->setMotionDetected(false);
}

void ReadPIRTask::execute()
{
    this->pir->sync();
    this->holder->setMotionDetected(this->pir->isDetected());
    this->context->checkUpdate(destCtx);
}
