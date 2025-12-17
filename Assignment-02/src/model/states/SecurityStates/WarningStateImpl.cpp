#include "WarningState.hpp"
#include "DangerState.hpp"

WarningState::WarningState(/* args */)
{
}

WarningState::~WarningState()
{
}

String WarningState::sendDRUData()
{
    return "Normal";
}

bool WarningState::canReceiveMsg()
{
    return false;
}

void WarningState::initializeTasks(HWPlatform *platform)
{
    // Implement the logic to initialize tasks specific to Danger state
}

void WarningState::changeState()
{
    context->setSecurityState(new DangerState());
}

String WarningState::getStateInfo()
{
    return "";
}