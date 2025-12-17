#pragma once

#include "../task.hpp"
#include "../../devices/servo_motor_impl.hpp"

class SweepingBWDTask : public Task
{

private:
    ServoMotorImpl *servo;

public:
    SweepingBWDTask(ServoMotorImpl *servo) : servo(servo) {};
    ~SweepingBWDTask();

    void excecute() override;
    void cleanup() override;
};