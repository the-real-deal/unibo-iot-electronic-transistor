#pragma once

#include "../Task.hpp"
#include "../../devices/Pir.h"
#include "../../model/states/Context.hpp"
#include "../../model/InputHolder.hpp"

class ReadPIRTask : public Task
{

private:
    Pir *pir;
    Context *context;
    InputHolder *holder;
    
public:
    ReadPIRTask(Pir *pir, Context *ctx, InputHolder *holder);
    virtual ~ReadPIRTask() = default;

    void execute() override;
    void cleanup() override;
};