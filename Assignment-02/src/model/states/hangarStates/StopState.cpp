#include "StopState.hpp"

StopState::StopState(HWPlatform *platform, InputHolder *holder) : HangarState(platform, holder)
{
    this->isIn = true;
}

void StopState::initializeTasks()
{
}

void StopState::checkUpdate()
{
}