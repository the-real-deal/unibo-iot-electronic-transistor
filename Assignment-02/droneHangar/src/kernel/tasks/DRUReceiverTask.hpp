#pragma once

#include "kernel/Task.hpp"
#include "devices/LCD.hpp"
#include "model/states/Context.hpp"

class DRUReceiverTask : public Task
{
private:
    Context *context;
    InputHolder *holder;
    ContextType destCtx;

public:
    DRUReceiverTask(Context *ctx, InputHolder *holder, ContextType type);
    ~DRUReceiverTask() = default;

    void execute() override;
    void cleanup() override;
};
