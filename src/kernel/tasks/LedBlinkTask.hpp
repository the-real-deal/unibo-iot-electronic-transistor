#pragma once

#include "../task.hpp"
#include "../../devices/LedExt.h"
#include "../../devices/Led.h"

class LedBlinkTask : public Task {

    private:
    LedExt led;
    int intensity;

    public:
    LedBlinkTask(LedExt led, int intensity) : led(led), intensity(intensity) {};
    ~LedBlinkTask();
    
    virtual void init() = 0;
    virtual void tick() = 0;
};