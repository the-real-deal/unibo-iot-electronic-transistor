#include "ServoMotorImpl.hpp"
#include "Arduino.h"

ServoMotorImpl::ServoMotorImpl() {}

ServoMotorImpl::ServoMotorImpl(int pin)
{
    this->pin = pin;
    this->angle = 0;
    this->motor.attach(pin, 500, 2740);
    this->motor.write(0);
    delay(500);
    this->motor.detach();
}

void ServoMotorImpl::on()
{
    this->motor.attach(pin, 500, 2740);
}

void ServoMotorImpl::setPosition(int angle)
{
    this->angle = angle;
    this->motor.write(angle);
}

void ServoMotorImpl::off()
{
    this->motor.detach();
}

int ServoMotorImpl::getPosition()
{
    return this->motor.read();
}