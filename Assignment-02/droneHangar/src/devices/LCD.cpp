#include "LCD.hpp"

LCD::LCD() {}

LCD::LCD(int address, int columns, int rows_) : lcd(new LiquidCrystal_I2C(address, columns, rows_)), rows(rows_)
{
    lcd->init();
    lcd->backlight();
}

void LCD::print(String text)
{
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print(text);
}
