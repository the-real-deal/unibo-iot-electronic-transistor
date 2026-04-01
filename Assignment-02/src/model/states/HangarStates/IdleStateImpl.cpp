#include "IdleState.hpp"
#include "kernel/tasks/LCDPrintTask.hpp"
#include "kernel/tasks/ReadTempTask.hpp"

IdleState::IdleState(/* args */)
{
}

IdleState::~IdleState()
{
}

void IdleState::initializeTasks(HWPlatform *platform, InputHolder *holder)
{
    Task* lcd = new LCDPrintTask(platform->getLCD(), "DRONE INSIDE");
    Task* temp = new ReadTempTask(platform->getTemperatureSensor(), this->context, NULL, ContextType::SECURITY);
    // DRU listener task
    // context->addTaskToScheduler(t);
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