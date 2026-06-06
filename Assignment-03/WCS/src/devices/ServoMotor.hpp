#pragma once

#include "devices/Device.hpp"
#include <Servo.h>

class ServoMotor : public Device
{

public:
    ServoMotor(int pin);
    ~ServoMotor() = default;

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