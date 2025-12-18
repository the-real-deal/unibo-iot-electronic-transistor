#pragma once

#include "../Task.hpp"
#include <string.h>
#include "../../devices/LCD.hpp"
#include "../../model/states/Context.hpp"

class LCDPrintTask : public Task
{
private:
    LCD *lcd;
    Context *context;

public:
    LCDPrintTask(LCD *lcd) : lcd(lcd) {};
    ~LCDPrintTask();

    virtual void init() = 0;
    virtual void tick() = 0;
};
