#pragma once


#include "../task.hpp"
#include "../../devices/Led.h"
#include "../../devices/LedExt.h"


class LedOnTask : public Task {

    private:
    Led led;

    public:
    LedOnTask(Led led) : led(led) {};
    ~LedOnTask();

    virtual void init() = 0;
    virtual void tick() = 0;
    
};
