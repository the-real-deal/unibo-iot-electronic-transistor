#pragma once

#include "../task.hpp"
#include <string.h>
#include "../../component/LCD.hpp"

class LCDPrintTask : public Task
{
private:
    LCD lcd;
    const char *message;

public:
    LCDPrintTask(LCD lcd, const char *message) : lcd(lcd), message(message) {};
    ~LCDPrintTask();
    bool excecute() override;
};
