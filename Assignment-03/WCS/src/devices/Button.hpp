#pragma once
#include "devices/Device.hpp"

class Button : public Device
{
public:
    Button(int pin);

    void init() override;

    /**
     * Checks if the button is currently pressed
     */
    bool isPressed();

private:
    int pin;
};
