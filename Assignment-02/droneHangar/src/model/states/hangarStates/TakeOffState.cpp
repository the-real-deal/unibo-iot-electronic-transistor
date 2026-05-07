#include "TakeOffState.hpp"
#include "OperativeState.hpp"
#include "kernel/tasks/LCDPrintTask.hpp"
#include "kernel/tasks/SweepingTask.hpp"
#include "kernel/tasks/ReadDistanceTask.hpp"
#include "kernel/tasks/LedBlinkTask.hpp"

TakeOffState::TakeOffState(HWPlatform *platform, InputHolder *holder) : HangarState(platform, holder)
{
    this->currentSubState = HangarSubState::OPENING;
    this->t = Timer();
    this->blinkTaskId = 0;
}

void TakeOffState::initializeTasks()
{
    this->addTask(
        new LCDPrintTask(
            this->hwPlatform->getLCD(),
            F("DRONE INSIDE")));

    this->addTask(
        new SweepingTask(
            this->hwPlatform->getServoMotor(),
            this->context,
            true,
            ContextType::HANGAR));

    this->addTask(
        new LedBlinkTask(this->hwPlatform->getLed2()));

    // remove taskid from added task, the queue is cleared multiple times during the state execution
    this->blinkTaskId = this->taskAdded.pop();
    // will be re-added before a context change
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
        // re-adding the task id
        this->taskAdded.add(this->blinkTaskId);
        this->context->setHangarState(new OperativeState(this->hwPlatform, this->inputHolder));
        break;
    }
}