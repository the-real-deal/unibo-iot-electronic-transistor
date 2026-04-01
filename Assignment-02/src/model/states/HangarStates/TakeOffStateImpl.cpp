#include "TakeOffState.hpp"

TakeOffState::TakeOffState(/* args */)
{
    this->currentSubState = HangarSubState::OPENING;
}

TakeOffState::~TakeOffState()
{
}

void TakeOffState::initializeTasks(HWPlatform *platform, InputHolder *holder)
{
    context->addTaskToScheduler(nullptr); // new LCDWrite();
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