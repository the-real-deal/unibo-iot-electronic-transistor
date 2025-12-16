#pragma once

#include "../task.hpp"
#include <string.h>
#include "../../devices/LCD.hpp"
#include "../../model/states/Context.hpp"

class LCDPrintTask : public Task
{
private:
    LCD *lcd;
    Context *context;
    const char *message;

public:
    LCDPrintTask(LCD *lcd_, Context *context_) : lcd(lcd_), context(context_) {};
    ~LCDPrintTask();
    void excecute() override;
};
