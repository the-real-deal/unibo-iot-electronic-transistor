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

void NormalState::recieveDRUData(String data)
{
}

void NormalState::initializeTasks(HWPlatform *platform)
{
    // Implement the logic to initialize tasks specific to Normal state
}

void NormalState::changeState()
{
    context->setSecurityState(new WarningState());
}

String NormalState::getStateInfo()
{
    return "";
}