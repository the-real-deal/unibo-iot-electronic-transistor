#include "DangerState.hpp"
#include "NormalState.hpp"
#include "model/states/hangarStates/IdleState.hpp"
#include "model/states/hangarStates/StopState.hpp"
#include "kernel/tasks/ButtonTask.hpp"

DangerState::DangerState(HWPlatform *platform, InputHolder *holder) : SecurityState(platform, holder) {}

bool DangerState::canReceiveMsg()
{
    return false;
}

void DangerState::initializeTasks()
{
    // halts the hangar and deletes his task inside the scheduler
    this->context->setHangarState(new StopState(this->hwPlatform, this->inputHolder));
    this->addTask(
        new ButtonTask(
            this->hwPlatform->getButton(),
            this->context,
            this->inputHolder,
            ContextType::SECURITY));
}

void DangerState::checkUpdate()
{
    if (this->inputHolder->isPressed())
    {
        // first start the hangar back up with the drone inside
        context->setHangarState(new IdleState(this->hwPlatform, this->inputHolder));
        // return to normal state
        context->setSecurityState(new NormalState(this->hwPlatform, this->inputHolder));
    }
}
