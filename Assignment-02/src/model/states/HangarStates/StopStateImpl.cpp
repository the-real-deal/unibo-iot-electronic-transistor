#include "StopState.hpp"

StopState::StopState()
{
    this->isIn = true;
}

StopState::~StopState() {}

void StopState::initializeTasks(HWPlatform *platform, InputHolder *holder)
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