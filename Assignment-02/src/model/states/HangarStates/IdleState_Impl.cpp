#include "IdleState.hpp"

IdleState::IdleState(/* args */)
{
}

IdleState::~IdleState()
{
}

void IdleState::initializeTasks(HWPlatform *platform)
{
    context->addTaskToScheduler(nullptr); // new LCDWrite();
}

String IdleState::sendDRUData()
{
    return "Drone In";
}

String IdleState::getStateInfo()
{
    return "Rest";
}

void IdleState::changeState()
{
    // Logic to change from Idle State to another state
}