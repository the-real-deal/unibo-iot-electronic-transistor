#include "TakeOffState.hpp"
#include "OperativeState.hpp"
#include "kernel/tasks/LCDPrintTask.hpp"
#include "kernel/tasks/SweepingTask.hpp"
#include "kernel/tasks/ReadDistanceTask.hpp"

TakeOffState::TakeOffState(HWPlatform *platform, InputHolder *holder) : HangarState(platform, holder)
{
    this->currentSubState = HangarSubState::OPENING;
    this->t = Timer();
}

void TakeOffState::initializeTasks()
{
    this->addTask(
        new LCDPrintTask(
            this->hwPlatform->getLCD(),
            "DRONE INSIDE"));

    this->addTask(
        new SweepingTask(
            this->hwPlatform->getServoMotor(),
            this->context,
            true,
            ContextType::HANGAR));
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
    /* Declared outside of the switch case to remove warnings */
    float d;
    switch (this->currentSubState)
    {
    case HangarSubState::CHECKING:
        break;
    case HangarSubState::OPENING:
        this->currentSubState = HangarSubState::DETECTING;
        this->removeAddedTasks();
        this->addTask(
            new ReadDistanceTask(
                this->hwPlatform->getDistanceDetector(),
                this->context,
                this->inputHolder,
                ContextType::HANGAR));
        break;
    case HangarSubState::DETECTING:
        // distance greater than D1 for T1 sec
        d = this->inputHolder->getDistance();
        if (!this->t.isRunning())
        {
            if (d > D1)
                this->t.init();
        }
        else
        {
            if (d <= D1)
                this->t.reset();
            else if (t.hasExeeded(T1))
            {
                this->currentSubState = HangarSubState::CLOSING;
                this->removeAddedTasks();
                this->addTask(
                    new SweepingTask(
                        this->hwPlatform->getServoMotor(),
                        this->context, false,
                        ContextType::HANGAR));
            }
        }

        break;
    case HangarSubState::CLOSING:
        this->context->setHangarState(new OperativeState(this->hwPlatform, this->inputHolder));
        break;
    }
}