#pragma once

#include "../task.hpp"
#include "../../devices/LCD.hpp"

class LCDReadTask : public Task {

    private:
    LCD lcd;
    

    public:
    LCDReadTask(LCD lcd) : lcd(lcd) {};
    ~LCDReadTask();
    
    virtual void init() = 0;
    virtual void tick() = 0;
    
};