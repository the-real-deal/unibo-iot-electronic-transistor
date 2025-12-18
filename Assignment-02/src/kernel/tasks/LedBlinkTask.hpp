#pragma once

#include "../task.hpp"
#include "../../devices/Led.h"

class LedBlinkTask : public Task
{

private:
    Led *led;
    bool ledIsOn;

public:
    LedBlinkTask(Led *led) : led(led) {};
    ~LedBlinkTask();

    void excecute() override;
    void cleanup() override;
};