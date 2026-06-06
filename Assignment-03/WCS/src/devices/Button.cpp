#include "devices/Button.hpp"
#include "Button.hpp"
#include <Arduino.h>

Button::Button(int pin) : pin(pin)
{
}

void Button::init()
{
    pinMode(this->pin, INPUT);
}

bool Button::isPressed()
{
    return digitalRead(this->pin) == HIGH;
}
