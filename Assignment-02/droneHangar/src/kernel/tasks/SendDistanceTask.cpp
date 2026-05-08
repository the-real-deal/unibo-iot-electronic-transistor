#include "SendDistanceTask.hpp"
#include "model/messageManager/MsgService.h"

SendDistanceTask::SendDistanceTask(InputHolder *inputHolder) : holder(inputHolder) {}

void SendDistanceTask::cleanup() {}

void SendDistanceTask::execute()
{
    MsgService.sendMsg(String(holder->getDistance()));
}