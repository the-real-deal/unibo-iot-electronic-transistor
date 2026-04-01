#pragma once
#include "kernel/Task.hpp"
#include "devices/TempSensor.h"
#include "model/states/Context.hpp"
#include "model/InputHolder.hpp"

class ReadTempTask : public Task
{

private:
    TempSensor *tempSensor;
    Context *context;
    InputHolder *holder;
    ContextType destCtx;
public:
    ReadTempTask(TempSensor *tempSensor, Context *ctx, InputHolder *holder, ContextType destCtx);
    virtual ~ReadTempTask() = default;

    void execute() override;
    void cleanup() override;
};