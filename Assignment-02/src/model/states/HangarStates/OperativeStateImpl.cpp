#include "OperativeState.hpp"

OperativeState::OperativeState(HWPlatform *platform, InputHolder *holder) : HangarState(platform, holder) {}

void OperativeState::initializeTasks()
{
    // Initialize tasks specific to the operative state
    // new Write LCD
}

String OperativeState::sendDRUData()
{
    return "Operative";
}

String OperativeState::getStateInfo()
{
    return "Drone Out";
}

void OperativeState::checkUpdate()
{
    // Logic to change state if needed
}