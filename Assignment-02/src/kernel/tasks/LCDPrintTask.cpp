#include "LCDPrintTask.hpp"
#include <Arduino.h>

LCDPrintTask::~LCDPrintTask()
{
}

void LCDPrintTask::excecute()
{
    String message = context->getStateInfo();
    lcd->print(1, message.c_str());
    this->setCompleted();
}
