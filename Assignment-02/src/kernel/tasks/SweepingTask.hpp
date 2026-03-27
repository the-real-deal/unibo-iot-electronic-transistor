#pragma once

#include "../Task.hpp"
#include "../../devices/servo_motor_impl.hpp"

class SweepingTask : public Task
{

private:
    ServoMotorImpl *servo;
    long stateTimestamp;
    int currentPos;
    int sweepConstant;
    int sweepSign;
    long elapsedSweepingTime();

public:
    SweepingTask(ServoMotorImpl *_servo, bool forward);
    virtual ~SweepingTask() = default;

    void execute() override;
    void cleanup() override;
};