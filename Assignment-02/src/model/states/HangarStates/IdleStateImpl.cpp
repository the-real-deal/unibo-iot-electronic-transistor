#include "IdleState.hpp"
#include "kernel/tasks/LCDPrintTask.hpp"
#include "kernel/tasks/ReadTempTask.hpp"
#include "kernel/tasks/DRUReceiverTask.hpp"
#include "model/states/HangarStates/TakeOffState.hpp"

IdleState::IdleState(HWPlatform *platform, InputHolder *holder) : HangarState(platform, holder) {}

void IdleState::initializeTasks()
{
    /* Tasks will be destroyed by the scheduler, since the state has no acces to it */
    this->addTask(new LCDPrintTask(this->hwPlatform->getLCD(), "DRONE INSIDE"));
    this->addTask(new ReadTempTask(this->hwPlatform->getTemperatureSensor(), this->context, this->inputHolder, ContextType::SECURITY));
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
    /**
     * Special case:
     * - the message receiver task will send the message to the context
     * - the context checks if the message is allowed to be processed (security state ok)
     * - the context delegates the request to the handle request method
     */
}

void IdleState::handleRequest(String msg)
{
    if(/*message is correct*/false)
    {
        this->context->setHangarState(new TakeOffState(this->hwPlatform, this->inputHolder));
    }
}