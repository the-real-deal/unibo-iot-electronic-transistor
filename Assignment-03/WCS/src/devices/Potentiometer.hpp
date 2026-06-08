#pragma once
#include "devices/Device.hpp"
class Potentiometer : public Device
{
public:
    Potentiometer(int pin);

    void init() override;

    /**
     * Gets the current potentiometer value.
     * @return A value between 0 an 1023
     */
    int getValue();

private:
    int pin;
};
