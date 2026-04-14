#include "NormalState.hpp"
#include "WarningState.hpp"

NormalState::NormalState(HWPlatform *platform, InputHolder *holder) : SecurityState(platform, holder)
{
}

String NormalState::sendDRUData()
{
    return "Normal";
}

bool NormalState::canReceiveMsg()
{
    return true;
}

void NormalState::initializeTasks()
{
    // Implement the logic to initialize tasks specific to Normal state
}

void NormalState::checkUpdate()
{
    // context->setSecurityState(new WarningState());
}

String NormalState::getStateInfo()
{
    return "";
}