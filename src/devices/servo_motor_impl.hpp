#pragma once

#include "servo_motor.hpp"
#include <Servo.h>

#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 180
#define SERVO_STEP_ANGLE 10

class ServoMotorImpl : public ServoMotor
{

public:
    ServoMotorImpl(int pin);

    void on();
    void setPosition(int angle);
    void off();

private:
    int pin;
    Servo motor;
};
