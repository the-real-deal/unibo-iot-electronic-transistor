#include "devices/Lcd.hpp"

LCD::LCD(int address, int columns, int rows_) : lcd(nullptr), address(address), columns(columns), rows(rows_)
{
}

void LCD::init()
{
    if (lcd == nullptr)
    {
        lcd = new LiquidCrystal_I2C(address, columns, rows);
        lcd->init();
        lcd->backlight();
    }
}

void LCD::print(String text)
{
    if (lcd != nullptr)
    {
        lcd->clear();
        lcd->setCursor(0, 0);
        lcd->print(text);
    }
}