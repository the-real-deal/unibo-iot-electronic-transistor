#pragma once

#include "../Task.hpp"
#include <string.h>
#include "../../devices/LCD.hpp"
#include "../../model/states/Context.hpp"

class LCDPrintTask : public Task
{
private:
    LCD *lcd;
    String text;

public:
    LCDPrintTask(LCD *lcd, String ttd);
    virtual ~LCDPrintTask() = default;

    void execute() override;
    void cleanup() override;
};
