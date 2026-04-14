#include "TakeOffState.hpp"

TakeOffState::TakeOffState(HWPlatform *platform, InputHolder *holder) : HangarState(platform, holder)
{
    this->currentSubState = HangarSubState::OPENING;
}

void TakeOffState::initializeTasks()
{
    // context->addTaskToScheduler(nullptr);
}

String TakeOffState::sendDRUData()
{
    return "TakeOff";
}

String TakeOffState::getStateInfo()
{
    return "Taking Off";
}

void TakeOffState::checkUpdate()
{
}