#pragma once

#include "../Task.hpp"
#include "../../devices/Pir.h"

class ReadPIRTask : public Task
{

private:
    Pir pir;

public:
    ReadPIRTask(Pir pir) : pir(pir) {};
    ~ReadPIRTask();

    void execute() override;
    void cleanup() override;
};