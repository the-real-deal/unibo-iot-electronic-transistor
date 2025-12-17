#pragma once

#include "../task.hpp"
#include "../../devices/Led.h"

class LedBlinkTask : public Task
{

private:
    Led *led;

public:
    LedBlinkTask(Led *led, int intensity) : led(led) {};
    ~LedBlinkTask();

    void excecute() override;
    void cleanup() override;
};