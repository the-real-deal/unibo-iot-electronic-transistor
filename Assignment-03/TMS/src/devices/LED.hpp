#pragma once
#include <Arduino.h>

class Led
{
public:
	Led(int _pin) : pin(_pin)
	{
		this->_isOn = false;
	}

	/**
	 * Initializes the led, this must be called in the setup function
	 */
	void init()
	{
		pinMode(this->pin, OUTPUT);
	}

	/**
	 * Turns on the led
	 */
	void switchOn()
	{
		digitalWrite(this->pin, HIGH);
		this->_isOn = true;
	}

	/**
	 * Turns off the led
	 */
	void switchOff()
	{
		digitalWrite(this->pin, LOW);
		this->_isOn = false;
	}

	/**
	 * Returns true if the led is on
	 */
	bool isOn()
	{
		return this->_isOn;
	}

protected:
	int pin;
	bool _isOn;
};