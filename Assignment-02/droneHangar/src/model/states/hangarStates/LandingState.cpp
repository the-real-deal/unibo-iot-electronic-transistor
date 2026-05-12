#include "LandingState.hpp"
#include "IdleState.hpp"
#include "kernel/tasks/SweepingTask.hpp"
#include "kernel/tasks/ReadDistanceTask.hpp"
#include "kernel/tasks/ReadPIRTask.hpp"
#include "kernel/tasks/LedBlinkTask.hpp"
#include "kernel/tasks/SendDistanceTask.hpp"
#include "model/messageManager/MsgService.h"

LandingState::LandingState(HWPlatform *platform, InputHolder *holder) : HangarState(platform, holder),
                                                                        currentSubState(HangarSubState::CHECKING),
                                                                        t(Timer()),
                                                                        blinkTaskId(0) {}

void LandingState::initializeTasks()
{
    // this->addTask(
    //     new LCDPrintTask(
    //         this->hwPlatform->getLCD(),
    //         F("LANDING")),
    //     0);
    this->hwPlatform->getLCD()->print(LANDING_STATE_MESSAGE);

    MsgService.sendMsg(LANDING_STATE_MESSAGE);

    this->addTask(
        new ReadPIRTask(
            this->hwPlatform->getPIR(),
            this->context,
            this->inputHolder,
            ContextType::HANGAR),
        0);

    this->addTask(
        new LedBlinkTask(this->hwPlatform->getLed2()), 500);

    // remove taskid from added task, the queue is cleared multiple times during the state execution
    this->blinkTaskId = this->taskAdded.pop();
    // will be re-added before a context change
}

void LandingState::checkUpdate()
{
    float d;
    switch (this->currentSubState)
    {
    case HangarSubState::CHECKING:
        if (this->inputHolder->isMotionDetected())
        {
            this->currentSubState = HangarSubState::OPENING;
            this->removeAddedTasks();
            this->addTask(
                new SweepingTask(
                    this->hwPlatform->getServoMotor(),
                    this->context,
                    true,
                    ContextType::HANGAR),
                0);
        }
        break;
    case HangarSubState::OPENING:
        this->currentSubState = HangarSubState::DETECTING;
        this->removeAddedTasks();
        this->addTask(
            new ReadDistanceTask(
                this->hwPlatform->getDistanceDetector(),
                this->context,
                this->inputHolder,
                ContextType::HANGAR),
            0);
        this->addTask(new SendDistanceTask(this->inputHolder), 250);
        break;
    case HangarSubState::DETECTING:
        d = this->inputHolder->getDistance();
        if (!this->t.isRunning())
        {
            if (d < D2)
                this->t.init();
        }
        else
        {
            if (d >= D2)
                this->t.reset();
            else if (t.hasExeeded(T2))
            {
                this->currentSubState = HangarSubState::CLOSING;
                this->removeAddedTasks();
                this->addTask(
                    new SweepingTask(
                        this->hwPlatform->getServoMotor(),
                        this->context,
                        false,
                        ContextType::HANGAR),
                    0);
            }
        }

        break;
    case HangarSubState::CLOSING:
        // re-adding the task id
        this->taskAdded.add(this->blinkTaskId);
        this->context->setHangarState(new IdleState(this->hwPlatform, this->inputHolder));
        break;
    default:
        break;
    }
}