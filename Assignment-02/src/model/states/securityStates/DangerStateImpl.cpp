#include "DangerState.hpp"
#include "NormalState.hpp"

DangerState::DangerState(HWPlatform *platform, InputHolder *holder) : SecurityState(platform, holder) {}

String DangerState::sendDRUData()
{
    return "Alarm";
}

bool DangerState::canReceiveMsg()
{
    return false;
}

void DangerState::initializeTasks()
{
    // platform->getButton()->enableInterrupt(this->checkUpdate());
    // this->context->setHangarState(nullptr /*STOP State*/);
}

void DangerState::checkUpdate()
{
    // context->setSecurityState(new NormalState());
}

String DangerState::getStateInfo()
{
    return "ALARM";
}