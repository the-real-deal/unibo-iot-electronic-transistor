#include "IdleState.hpp"
#include "kernel/tasks/LCDPrintTask.hpp"
#include "kernel/tasks/ReadTempTask.hpp"
#include "kernel/tasks/DRUReceiverTask.hpp"

IdleState::IdleState(/* args */)
{

}

IdleState::~IdleState()
{
}

void IdleState::initializeTasks(HWPlatform *platform, InputHolder *holder)
{
    this->addTask(new LCDPrintTask(platform->getLCD(), "DRONE INSIDE"));
    this->addTask(new ReadTempTask(platform->getTemperatureSensor(), this->context, holder, ContextType::SECURITY));
    this->addTask(new DRUReceiverTask(this->context));
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

void IdleState::handleRequest(String msg)
{
    if(/*message is correct*/false)
    {
        
    }
}