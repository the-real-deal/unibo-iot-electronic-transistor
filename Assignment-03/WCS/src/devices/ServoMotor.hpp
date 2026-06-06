#pragma once

#include "devices/Device.hpp"
#include <Servo.h>

class ServoMotorImpl : public Device
{

public:
    ServoMotorImpl(int pin);
    ~ServoMotorImpl() = default;

    void init() override;
    void on();
    void setPosition(int angle);
    void off();
    int getPosition();

private:
    int pin;
    int angle;
    Servo motor;
};