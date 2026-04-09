#include "DRUReceiverTask.hpp"

DRUReceiverTask::DRUReceiverTask(Context *ctx) : context(ctx) {}

void DRUReceiverTask::execute()
{
    String msg = "[TODO] read from serial";
    if(msg.length() > 0)
        this->context->handleDRURequest(msg);
}

void DRUReceiverTask::cleanup() {}