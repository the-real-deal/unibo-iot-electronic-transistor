#pragma once

#include "kernel/Task.hpp"
#include "devices/Led.h"

class LedBlinkTask : public Task
{

private:
    Led *led;

public:
    LedBlinkTask(Led *led);
    ~LedBlinkTask() = default;

    void execute() override;
    void cleanup() override;
};