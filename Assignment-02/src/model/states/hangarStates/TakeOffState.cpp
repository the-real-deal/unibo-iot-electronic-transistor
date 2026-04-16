#include "TakeOffState.hpp"
#include "model/Timer.hpp"
#include "kernel/tasks/LCDPrintTask.hpp"
#include "kernel/tasks/SweepingTask.hpp"

TakeOffState::TakeOffState(HWPlatform *platform, InputHolder *holder) : HangarState(platform, holder)
{
    this->currentSubState = HangarSubState::OPENING;
}

void TakeOffState::initializeTasks()
{
    this->context->addTaskToScheduler(new LCDPrintTask(this->hwPlatform->getLCD(), "DRONE INSIDE"));
    this->context->addTaskToScheduler(new SweepingTask(this->hwPlatform->getServoMotor(), true));
}

String TakeOffState::sendDRUData()
{
    return "TakeOff";
}

String TakeOffState::getStateInfo()
{
    return "Taking Off";
}

void TakeOffState::checkUpdate()
{
}