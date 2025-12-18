#include "LCDPrintTask.hpp"

LCDPrintTask::~LCDPrintTask()
{
}

void LCDPrintTask::init()
{
    Task::init();
}

void LCDPrintTask::tick()
{
    lcd->print(1, "");
    setCompleted();
}
