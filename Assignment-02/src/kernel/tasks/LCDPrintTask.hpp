#pragma once

#include "../Task.hpp"
#include <string.h>
#include "../../devices/LCD.hpp"

class LCDPrintTask : public Task
{
private:
    LCD lcd;
    const char *message;

public:
    LCDPrintTask(LCD lcd, const char *message) : lcd(lcd), message(message) {};
    ~LCDPrintTask();

    virtual void init() = 0;
    virtual void tick() = 0;
};
