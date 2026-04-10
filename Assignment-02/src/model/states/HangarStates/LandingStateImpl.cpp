#include "LandingState.hpp"

LandingState::LandingState(HWPlatform *platform, InputHolder *holder) : HangarState(platform, holder)
{
    this->currentSubState = HangarSubState::CHECKING;
}

void LandingState::initializeTasks()
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

void LandingState::checkUpdate()
{
}