#include "DRUReceiverTask.hpp"
#include "model/messageManager/MsgService.h"
#include "model/messageManager/Logger.h"

DRUReceiverTask::DRUReceiverTask(Context *ctx, InputHolder *holder, ContextType type) : context(ctx),
                                                                                        holder(holder),
                                                                                        destCtx(type) {}

DRUReceiverTask::~DRUReceiverTask()
{
    cleanup();
}

void DRUReceiverTask::execute()
{
    if (MsgService.isMsgAvailable())
    {
        Msg *msg = MsgService.receiveMsg();
        this->holder->setMessage(msg->getContent());
        this->context->handleDRURequest();
    }
}

void DRUReceiverTask::cleanup()
{
    // this->holder->setMessage();
}