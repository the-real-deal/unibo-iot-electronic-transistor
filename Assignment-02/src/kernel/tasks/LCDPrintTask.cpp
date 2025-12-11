#include "LCDPrintTask.hpp"

LCDPrintTask::~LCDPrintTask()
{
}

bool LCDPrintTask::excecute()
{
    lcd.print(1, message);
    return true; // Indicate that the task is finished
}
