#include "Led.h"
#include <Arduino.h>

Led::Led(int pin)
{
  this->pin = pin;
  this->_isOn = false;
  pinMode(pin, OUTPUT);
}

void Led::switchOn()
{
  digitalWrite(pin, HIGH);
  this->_isOn = true;
}

void Led::switchOff()
{
  digitalWrite(pin, LOW);
  this->_isOn = false;
};

bool Led::isOn()
{
  return this->_isOn;
}
