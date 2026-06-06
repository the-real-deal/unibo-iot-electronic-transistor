#include <Arduino.h>
#include "ServoMotor.hpp"

ServoMotorImpl::ServoMotorImpl(int pin)
{
    this->pin = pin;
    this->angle = 0;
}

void ServoMotorImpl::on()
{
    this->motor.attach(pin, 500, 2740);
}

void ServoMotorImpl::init()
{
    this->motor.attach(pin, 500, 2740);
    this->motor.write(0);
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