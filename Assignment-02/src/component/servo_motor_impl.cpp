#include "servo_motor_impl.hpp"
#include "Arduino.h"

ServoMotorImpl::ServoMotorImpl(int pin)
{
    this->pin = pin;
}

void ServoMotorImpl::on()
{
    motor.attach(pin, 500, 2740);
}

void ServoMotorImpl::setPosition(int angle)
{
    motor.write(angle);
}

void ServoMotorImpl::off()
{
    motor.detach();
}