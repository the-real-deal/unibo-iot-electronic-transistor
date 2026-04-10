#include "WarningState.hpp"
#include "DangerState.hpp"

WarningState::WarningState(HWPlatform *platform, InputHolder *holder) : SecurityState(platform, holder) {}

String WarningState::sendDRUData()
{
    return "Normal";
}

bool WarningState::canReceiveMsg()
{
    return false;
}

void WarningState::initializeTasks()
{
    // Implement the logic to initialize tasks specific to Danger state
}

void WarningState::checkUpdate()
{
    // context->setSecurityState(new DangerState());
}

String WarningState::getStateInfo()
{
    return "";
}