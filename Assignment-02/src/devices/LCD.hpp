#pragma once
#include <LiquidCrystal_I2C.h>

class LCD
{
private:
    LiquidCrystal_I2C *lcd;
    int rows = 0;

public:
    LCD(int address, int columns, int rows_);
    virtual ~LCD() {};
    void print(const int nRows, ...);
};
