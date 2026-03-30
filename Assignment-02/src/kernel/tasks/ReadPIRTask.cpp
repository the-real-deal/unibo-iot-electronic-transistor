#include "ReadPIRTask.hpp"

ReadPIRTask::ReadPIRTask(Pir *pir, Context *ctx, InputHolder *holder): pir(pir), context(ctx), holder(holder) {}

void ReadPIRTask::cleanup()
{
}

void ReadPIRTask::execute()
{
    bool isDetected = pir->isDetected();
    holder->setMotionDetected(isDetected);
    // value holder.pirDetected = pir->isDetected();
}
