#include "LandingState.hpp"

LandingState::LandingState(/* args */)
{
    this->currentSubState = HangarSubState::CHECKING;
}

LandingState::~LandingState()
{
}

void LandingState::initializeTasks(HWPlatform *platform)
{
    context->addTaskToScheduler(nullptr); // new LCDWrite();
}

String LandingState::sendDRUData()
{
    return "Landing";
}

String LandingState::getStateInfo()
{
    return "Landing";
}

void LandingState::changeState()
{
}