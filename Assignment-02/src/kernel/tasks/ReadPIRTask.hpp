#pragma once

#include "../Task.hpp"
#include "../../devices/Pir.h"

class ReadPIRTask : public Task
{

private:
    Pir *pir;

public:
    ReadPIRTask(Pir *pir);
    virtual ~ReadPIRTask() = default;

    void execute() override;
    void cleanup() override;
};