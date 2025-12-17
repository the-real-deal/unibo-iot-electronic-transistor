#pragma once

#include "../task.hpp"
#include "../../devices/PirImpl.hpp"

class ReadPIRTask : public Task {

    private:
    Pir pir;

    public:
    ReadPIRTask(Pir pir) : pir(pir) {};
    ~ReadPIRTask();
    
    virtual void init() = 0;
    virtual void tick() = 0;
};