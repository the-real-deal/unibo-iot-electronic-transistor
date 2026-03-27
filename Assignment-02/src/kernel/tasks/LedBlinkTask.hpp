#pragma once

#include "../Task.hpp"
#include "../../devices/Led.h"

class LedBlinkTask : public Task
{

private:
    Led *led;

public:
    LedBlinkTask(Led *led);
    virtual ~LedBlinkTask() = default;

    void execute() override;
    void cleanup() override;
};