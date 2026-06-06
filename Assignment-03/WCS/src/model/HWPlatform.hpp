#pragma once
#include "devices/Device.hpp"
#include "devices/Button.hpp"
#include "devices/Lcd.hpp"
#include "devices/Potentiometer.hpp"
#include "devices/ServoMotor.hpp"
#include "configs.h"

class HWPlatform : public Device
{
public:
    HWPlatform() : btn(new Button(BUTTON_PIN)),
                   lcd(new LCD(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS)),
                   pot(new Potentiometer(POTENTIOMETER_PIN)),
                   motor(new ServoMotor(SERVO_PIN))
    {
    }
    ~HWPlatform() = default;

    void init() override
    {
        this->btn->init();
        this->lcd->init();
        this->pot->init();
        this->motor->init();
    }

    Button *getButton()
    {
        return this->btn;
    }

    LCD *getLCD()
    {
        return this->lcd;
    }

    Potentiometer *getPotentiometer()
    {
        return this->pot;
    }

    ServoMotor *getServoMotor()
    {
        return this->motor;
    }

private:
    Button *btn;
    LCD *lcd;
    Potentiometer *pot;
    ServoMotor *motor;
};
