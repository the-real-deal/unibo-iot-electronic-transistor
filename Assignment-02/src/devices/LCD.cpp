#include "LCD.hpp"

LCD::LCD(int address, int columns, int rows_)
{
    lcd = new LiquidCrystal_I2C(address, columns, rows_);
    rows = rows_;
    lcd->init();
    lcd->backlight();
}

void LCD::print(const int nRows, ...)
{
    va_list args;
    va_start(args, nRows);

    lcd->clear();

    int i = 0;
    while (i < nRows && i < this->rows)
    {
        const char *line = va_arg(args, const char *);
        lcd->setCursor(0, i);
        lcd->print(line);
        i++;
    }
}
