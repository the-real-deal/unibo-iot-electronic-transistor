#pragma once

#include "../task.hpp"
#include "../../devices/Led.h"

class LedBlinkTask : public Task
{

private:
    Led *led;

public:
    LedBlinkTask(Led *led) : led(led) {};
    ~LedBlinkTask();

    void execute() override;
    void cleanup() override;
};