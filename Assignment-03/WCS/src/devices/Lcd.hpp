#pragma once
#include "devices/Device.hpp"
#include <LiquidCrystal_I2C.h>

class LCD : public Device
{
public:
    LCD(int address, int columns, int rows_);
    ~LCD() = default;

    void init() override;

    /**
     * Prints the string in the lcd
     */
    void print(String text);

private:
    LiquidCrystal_I2C *lcd;
    int address;
    int rows;
    int columns;
};