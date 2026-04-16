#pragma once

#include "kernel/Task.hpp"
#include "devices/ServoMotor.hpp"

class SweepingTask : public Task
{

private:
    ServoMotor *servo;
    long stateTimestamp;
    int currentPos;
    int sweepConstant;
    int sweepSign;
    long elapsedSweepingTime();

public:
    SweepingTask(ServoMotor *_servo, bool forward);
    ~SweepingTask() = default;

    void execute() override;
    void cleanup() override;
};