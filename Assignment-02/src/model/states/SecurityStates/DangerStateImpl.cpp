#include "DangerState.hpp"
#include "NormalState.hpp"

DangerState::DangerState(/* args */)
{
}
DangerState::~DangerState()
{
}

String DangerState::sendDRUData()
{
    return "Alarm";
}

bool DangerState::canReceiveMsg()
{
    return false;
}

void DangerState::initializeTasks(HWPlatform *platform)
{
    // platform->getButton()->enableInterrupt(this->changeState());
    this->context->setHangarState(nullptr /*STOP State*/);
}

void DangerState::changeState()
{
    context->setSecurityState(new NormalState());
}

String DangerState::getStateInfo()
{
    return "ALARM";
}