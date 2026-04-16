#include "StopState.hpp"

StopState::StopState(HWPlatform *platform, InputHolder *holder) : HangarState(platform, holder)
{
    this->isIn = true;
}

void StopState::initializeTasks()
{
    // Initialize tasks specific to the stop state
    // new SWPBWD();
}

String StopState::sendDRUData()
{
    return "";
}

String StopState::getStateInfo()
{
    return "";
}

void StopState::checkUpdate()
{
}