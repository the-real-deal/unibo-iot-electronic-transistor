#pragma once

#include <string.h>
#include "kernel/Task.hpp"
#include "devices/LCD.hpp"
#include "model/states/Context.hpp"

class DRUReceiverTask : public Task
{
private:
    Context *context;
    InputHolder *holder;

public:
    DRUReceiverTask(Context *ctx);
    virtual ~DRUReceiverTask() = default;

    void execute() override;
    void cleanup() override;
};
