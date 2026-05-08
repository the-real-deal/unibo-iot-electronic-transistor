#include "OperativeState.hpp"
#include "LandingState.hpp"
#include "kernel/tasks/DRUReceiverTask.hpp"

OperativeState::OperativeState(HWPlatform *platform, InputHolder *holder) : HangarState(platform, holder) {}

void OperativeState::initializeTasks()
{
    // this->addTask(
    //     new LCDPrintTask(
    //         this->hwPlatform->getLCD(),
    //         F("DRONE OUT")),
    //     0);

    this->hwPlatform->getLCD()->print(F("Drone Out"));

    this->addTask(
        new DRUReceiverTask(
            this->context,
            this->inputHolder,
            ContextType::HANGAR),
        0);
}

void OperativeState::checkUpdate()
{
    if (/*message is correct*/ false)
    {
        this->context->setHangarState(new LandingState(this->hwPlatform, this->inputHolder));
    }
}