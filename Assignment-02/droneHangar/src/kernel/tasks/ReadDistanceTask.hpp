#pragma once

#include "kernel/Task.hpp"
#include "devices/Sonar.h"
#include "model/states/Context.hpp"
#include "model/InputHolder.hpp"

class ReadDistanceTask : public Task
{

private:
    ProximitySensor *sonar;
    Context *context;
    InputHolder *holder;
    ContextType destCtx;

public:
    ReadDistanceTask(ProximitySensor *sonar, Context *ctx, InputHolder *valHolder, ContextType type);
    ~ReadDistanceTask() = default;

    void execute() override;
    void cleanup() override;
};