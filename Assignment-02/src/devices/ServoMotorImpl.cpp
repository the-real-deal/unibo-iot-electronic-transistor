#include "ServoMotorImpl.hpp"
#include "Arduino.h"

ServoMotorImpl::ServoMotorImpl() {}

ServoMotorImpl::ServoMotorImpl(int pin)
{
    this->pin = pin;
    this->angle = 0;
}

void ServoMotorImpl::on()
{
    motor.attach(pin);
}

void ServoMotorImpl::setPosition(int angle)
{
    this->angle = angle;
    motor.write(angle);
}

void ServoMotorImpl::off()
{
    motor.detach();
}

int ServoMotorImpl::getPosition()
{
    return motor.read();
}