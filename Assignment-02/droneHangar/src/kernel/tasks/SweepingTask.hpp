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
    int sweepSign;
    bool hasJustEntered;
    int destination;

    long elapsedSweepingTime();

public:
    /**
     * If forward is true, the destination angle is 180
     */
    SweepingTask(ServoMotorImpl *_servo, Context *context, bool forward, ContextType destCtx);
    ~SweepingTask() = default;

    void execute() override;
    void cleanup() override;
};