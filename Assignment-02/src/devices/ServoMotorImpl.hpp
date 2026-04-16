#pragma once

#include "ServoMotor.hpp"
#include <Servo.h>

class ServoMotorImpl : public ServoMotor
{

public:
    ServoMotorImpl(int pin);

    void on();
    void setPosition(int angle);
    void off();
    int getPosition() { return angle; }

private:
    int pin;
    int angle;
    Servo motor;
};
