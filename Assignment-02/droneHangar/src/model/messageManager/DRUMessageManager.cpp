#include "MsgService.h"
#include "DRUMessageManager.hpp"

String DRUMessageManager::receiveMSG()
{
    return MsgService.receiveMsg()->getContent();
}

void DRUMessageManager::sendMSG(const String &msg)
{
    MsgService.sendMsg(msg);
}