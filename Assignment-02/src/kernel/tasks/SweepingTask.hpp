#pragma once

#include "kernel/Task.hpp"
#include "devices/ServoMotor.hpp"
#include "model/states/Context.hpp"

class SweepingTask : public Task
{

private:
    ServoMotorImpl *servo;
    Context *ctx;
    ContextType destContext;
    // long stateTimestamp;
    // int currentPos;
    // int sweepConstant;
    int sweepSign;
    bool hasJustEntered;
    int destination;

    long elapsedSweepingTime();

public:
    SweepingTask(ServoMotorImpl *_servo, Context *context, bool forward, ContextType destCtx);
    ~SweepingTask() = default;

    void execute() override;
    void cleanup() override;
};