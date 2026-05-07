#pragma once

#include "ServoMotor.hpp"
#include <Servo.h>

class ServoMotorImpl : public ServoMotor
{

public:
    ServoMotorImpl();
    ServoMotorImpl(int pin);
    ~ServoMotorImpl() = default;

    void on();
    void setPosition(int angle);
    void off();
    int getPosition();

private:
    int pin;
    int angle;
    Servo motor;
};
