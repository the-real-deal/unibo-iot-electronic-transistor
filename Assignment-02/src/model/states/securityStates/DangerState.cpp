#include "DangerState.hpp"
#include "NormalState.hpp"
#include "model/states/hangarStates/IdleState.hpp"
#include "model/states/hangarStates/StopState.hpp"
#include "kernel/tasks/ButtonTask.hpp"

DangerState::DangerState(HWPlatform *platform, InputHolder *holder) : SecurityState(platform, holder) {}

String DangerState::sendDRUData()
{
    return "Alarm";
}

bool DangerState::canReceiveMsg()
{
    return false;
}

void DangerState::initializeTasks()
{
    this->addTask(
        new ButtonTask(
            this->hwPlatform->getButton(),
            this->context,
            this->inputHolder,
            ContextType::SECURITY));

    this->context->setHangarState(new StopState(this->hwPlatform, this->inputHolder));
}

void DangerState::checkUpdate()
{
    if (this->inputHolder->isPressed())
    {
        context->setHangarState(new IdleState(this->hwPlatform, this->inputHolder));
        context->setSecurityState(new NormalState(this->hwPlatform, this->inputHolder));
    }
}

String DangerState::getStateInfo()
{
    return "ALARM";
}