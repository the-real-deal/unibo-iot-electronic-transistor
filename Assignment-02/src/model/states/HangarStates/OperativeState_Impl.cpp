#include "OperativeState.hpp"

OperativeState::OperativeState(/* args */) {}

OperativeState::~OperativeState() {}

void OperativeState::initializeTasks(HWPlatform *platform)
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

void OperativeState::changeState()
{
    // Logic to change state if needed
}