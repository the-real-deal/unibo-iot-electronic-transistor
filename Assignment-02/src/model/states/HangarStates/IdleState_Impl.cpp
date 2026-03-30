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
    return "Rest";
}

String IdleState::getStateInfo()
{
    return "Drone In";
}

void IdleState::checkUpdate()
{
    // Logic to change from Idle State to another state
}