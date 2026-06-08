#include "devices/Potentiometer.hpp"
#include <Arduino.h>
#include "Potentiometer.hpp"

Potentiometer::Potentiometer(int pin)
{
    this->pin = pin;
}

void Potentiometer::init()
{
    // not needed
}

int Potentiometer::getValue()
{
    return analogRead(pin);
}
