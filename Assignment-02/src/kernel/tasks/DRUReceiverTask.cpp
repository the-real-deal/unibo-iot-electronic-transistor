#include "DRUReceiverTask.hpp"

DRUReceiverTask::DRUReceiverTask(Context *ctx,InputHolder *holder, ContextType type) : context(ctx),holder(holder), destCtx(type) {}

void DRUReceiverTask::execute()
{
    String msg = "[TODO] read from serial";
    if(msg.length() > 0 && /*message is directed to controller*/ true )
    {
        this->holder->setMessage(msg);
        this->context->handleDRURequest();
    }
}

void DRUReceiverTask::cleanup() {}