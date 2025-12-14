#pragma once

#include "../task.hpp"
#include <string.h>
#include "../../devices/LCD.hpp"

class LCDPrintTask : public Task
{
private:
    LCD *lcd;
    const char *message;

public:
    LCDPrintTask(LCD *lcd) : lcd(lcd) {};
    ~LCDPrintTask();
    bool excecute() override;
};
