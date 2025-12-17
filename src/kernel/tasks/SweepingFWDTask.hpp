#pragma once

#include "../task.hpp"
#include "../../devices/servo_motor_impl.hpp"


class SweepingFWDTask : public Task {

    private:
    ServoMotorImpl servo;

    public:
    SweepingFWDTask(ServoMotorImpl servo) : servo(servo) {};
    ~SweepingFWDTask();

    virtual void init() = 0;
    virtual void tick() = 0;
};