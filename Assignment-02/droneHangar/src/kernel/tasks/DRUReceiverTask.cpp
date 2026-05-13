#include "DRUReceiverTask.hpp"
#include "model/messageManager/MsgService.h"
#include "model/messageManager/Logger.h"

DRUReceiverTask::DRUReceiverTask(Context *ctx, InputHolder *holder, ContextType type) : context(ctx),
                                                                                        holder(holder),
                                                                                        destCtx(type) {}

void DRUReceiverTask::execute()
{
    if (MsgService.isMsgAvailable())
    {
        Msg *msg = MsgService.receiveMsg();
        this->holder->setMessage(msg->getContent());
        delete msg;
        this->context->handleDRURequest();
    }
}

void DRUReceiverTask::cleanup()
{
    // this->holder->setMessage();
}