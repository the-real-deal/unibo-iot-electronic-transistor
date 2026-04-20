#include "LandingState.hpp"
#include "IdleState.hpp"
#include "kernel/tasks/LCDPrintTask.hpp"
#include "kernel/tasks/SweepingTask.hpp"
#include "kernel/tasks/ReadDistanceTask.hpp"
#include "kernel/tasks/ReadPIRTask.hpp"

LandingState::LandingState(HWPlatform *platform, InputHolder *holder) : HangarState(platform, holder)
{
    this->currentSubState = HangarSubState::CHECKING;
    this->t = Timer();
}

void LandingState::initializeTasks()
{
    this->context->addTaskToScheduler(
        new LCDPrintTask(
            this->hwPlatform->getLCD(),
            "LANDING"));

    this->context->addTaskToScheduler(
        new ReadPIRTask(
            this->hwPlatform->getPIR(),
            this->context,
            this->inputHolder,
            ContextType::HANGAR));
}

String LandingState::sendDRUData()
{
    return "Landing";
}

String LandingState::getStateInfo()
{
    return "Landing";
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
            this->context->addTaskToScheduler(
                new SweepingTask(
                    this->hwPlatform->getServoMotor(),
                    this->context,
                    true,
                    ContextType::HANGAR));
        }
        break;
    case HangarSubState::OPENING:
        this->currentSubState = HangarSubState::DETECTING;
        this->removeAddedTasks();
        this->context->addTaskToScheduler(
            new ReadDistanceTask(
                this->hwPlatform->getDistanceDetector(),
                this->context,
                this->inputHolder,
                ContextType::HANGAR));
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
                this->context->addTaskToScheduler(
                    new SweepingTask(
                        this->hwPlatform->getServoMotor(),
                        this->context, false,
                        ContextType::HANGAR));
            }
        }

        break;
    case HangarSubState::CLOSING:
        this->context->setHangarState(new IdleState(this->hwPlatform, this->inputHolder));
        break;
    default:
        break;
    }
}