#pragma once

#include "kernel/Task.hpp"
#include "devices/ServoMotor.hpp"
#include "model/states/Context.hpp"

class SweepingTask : public Task
{

private:
    ServoMotor *servo;
    Context *ctx;
    ContextType destContext;
    long stateTimestamp;
    int currentPos;
    int sweepConstant;
    int sweepSign;
    long elapsedSweepingTime();

public:
    SweepingTask(ServoMotor *_servo, Context *context, bool forward, ContextType destCtx);
    ~SweepingTask() = default;

    void execute() override;
    void cleanup() override;
};