#include "OperativeState.hpp"
#include "LandingState.hpp"
#include "kernel/tasks/DRUReceiverTask.hpp"
#include "model/messageManager/MsgService.h"

OperativeState::OperativeState(HWPlatform *platform, InputHolder *holder) : HangarState(platform, holder) {}

void OperativeState::initializeTasks()
{
    this->hwPlatform->getLCD()->print(OPERATING_STATE_MESSAGE);
    MsgService.sendMsg(OPERATING_STATE_MESSAGE);

    this->addTask(
        new DRUReceiverTask(
            this->context,
            this->inputHolder,
            ContextType::HANGAR),
        0);
}

void OperativeState::checkUpdate()
{
    if (inputHolder->getMessage() == LANDING_STATE_MESSAGE)
    {
        this->context->setHangarState(new LandingState(this->hwPlatform, this->inputHolder));
    }
}