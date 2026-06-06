#include <Arduino.h>
#include "ServoMotor.hpp"

ServoMotor::ServoMotor(int pin)
{
    this->pin = pin;
    this->angle = 0;
}

void ServoMotor::on()
{
    this->motor.attach(pin, 500, 2740);
}

void ServoMotor::init()
{
    this->motor.attach(pin, 500, 2740);
    this->motor.write(0);
}

void ServoMotor::setPosition(int angle)
{
    this->angle = angle;
    this->motor.write(angle);
}

void ServoMotor::off()
{
    this->motor.detach();
}

int ServoMotor::getPosition()
{
    return this->motor.read();
}