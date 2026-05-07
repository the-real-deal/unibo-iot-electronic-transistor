#include "IdleState.hpp"
#include "TakeOffState.hpp"
#include "kernel/tasks/LCDPrintTask.hpp"
#include "kernel/tasks/ReadTempTask.hpp"
#include "kernel/tasks/DRUReceiverTask.hpp"

IdleState::IdleState(HWPlatform *platform, InputHolder *holder) : HangarState(platform, holder) {}

void IdleState::initializeTasks()
{
    /* Tasks will be destroyed by the scheduler, since the state has no acces to it */
    this->addTask(
        new LCDPrintTask(
            this->hwPlatform->getLCD(),
            F("DRONE INSIDE")),
        0);

    this->addTask(
        new ReadTempTask(
            this->hwPlatform->getTemperatureSensor(),
            this->context, this->inputHolder,
            ContextType::SECURITY),
        0);

    this->addTask(
        new DRUReceiverTask(
            this->context,
            this->inputHolder,
            ContextType::HANGAR),
        0);
}

void IdleState::checkUpdate()
{
    if (/*message is correct*/ false)
    {
        this->context->setHangarState(new TakeOffState(this->hwPlatform, this->inputHolder));
    }
}