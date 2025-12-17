#include "LedOnTask.hpp"

LedOnTask::~LedOnTask()
{
}

void LedOnTask::init()
{
    Task::init();
}

void LedOnTask::tick()
{
    led.switchOn();
    setCompleted();
}
