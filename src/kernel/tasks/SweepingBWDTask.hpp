#pragma once

#include "../task.hpp"
#include "../../devices/servo_motor_impl.hpp"


class SweepingBWDTask : public Task {

    private:
    ServoMotorImpl servo;

    public:
    SweepingBWDTask(ServoMotorImpl servo) : servo(servo) {};
    ~SweepingBWDTask();
 
    virtual void init() = 0;
    virtual void tick() = 0;
};