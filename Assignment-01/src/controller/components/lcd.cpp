#include "lcd.h"
#include <LiquidCrystal_I2C.h>
#include <stdarg.h>
#include <string.h>
#include <Wire.h>
#include <Arduino.h>
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setupLcd()
{
    lcd.init();
    lcd.backlight();
}

void printToLcd(const int nRows, ...)
{
    va_list args;
    va_start(args, nRows);

    lcd.clear();

    int i = 0;
    while (i < nRows && i < LCD_ROWS)
    {
        const char *line = va_arg(args, const char *);
        lcd.setCursor(0, i);
        lcd.print(line);
        i++;
    }
}
