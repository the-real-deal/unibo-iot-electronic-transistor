#include "LCD.hpp"
#include "Arduino.h"

LCD::LCD(int address, int columns, int rows) : lcd(address, columns, rows)
{
    lcd.init();
    lcd.backlight();
}

void LCD::print(const int nRows, ...)
{
    va_list args;
    va_start(args, nRows);

    lcd.clear();

    int i = 0;
    while (i < nRows && i < this->rows)
    {
        const char *line = va_arg(args, const char *);
        lcd.setCursor(0, i);
        lcd.print(line);
        i++;
    }
}
