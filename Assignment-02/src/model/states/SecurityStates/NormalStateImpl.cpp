#include "NormalState.hpp"
#include "WarningState.hpp"

NormalState::NormalState(/* args */)
{
}
NormalState::~NormalState()
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

void NormalState::initializeTasks(HWPlatform *platform, InputHolder *holder)
{
    // Implement the logic to initialize tasks specific to Normal state
}

void NormalState::checkUpdate()
{
    context->setSecurityState(new WarningState());
}

String NormalState::getStateInfo()
{
    return "";
}