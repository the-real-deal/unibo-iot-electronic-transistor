#pragma once

#include "devices/ButtonImpl.h"
#include "devices/Led.h"
#include "devices/Pir.h"
#include "devices/LCD.hpp"
#include "devices/Sonar.h"
#include "devices/TempSensorImpl.h"
#include "devices/ServoMotorImpl.hpp"

class HWPlatform
{
public:
    HWPlatform() : _button(ButtonImpl(BUTTON1)),
                   _led2(Led(LED2)),
                   _led3(Led(LED3)),
                   _pir(Pir(PIR_PIN)),
                   _lcd(LCD(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS)),
                   _distanceDetector(Sonar(SONAR_ECHO_PIN, SONAR_TRIG_PIN, 30000)),
                   _temperatureSensor(TempSensorDHT11(DHTPIN)),
                   _servo(ServoMotorImpl(SERVO_PIN)) {};

    ~HWPlatform() {
        // delete _button;
        // delete _led2;
        // delete _led3;
        // delete _pir;
        // delete _lcd;
        // delete _distanceDetector;
        // delete _temperatureSensor;
        // delete _servo;
    };

    ButtonImpl *getButton()
    {
        return &this->_button;
    };

    Led *getLed2()
    {
        return &this->_led2;
    }

    Led *getLed3()
    {
        return &this->_led3;
    }

    Pir *getPIR()
    {
        return &this->_pir;
    }

    LCD *getLCD()
    {
        return &this->_lcd;
    }

    Sonar *getDistanceDetector()
    {
        return &this->_distanceDetector;
    }

    TempSensorDHT11 *getTemperatureSensor()
    {
        return &this->_temperatureSensor;
    }

    ServoMotorImpl *getServoMotor()
    {
        return &this->_servo;
    }

private:
    ButtonImpl _button;
    Led _led2;
    Led _led3;
    Pir _pir;
    LCD _lcd;
    Sonar _distanceDetector;
    TempSensorDHT11 _temperatureSensor;
    ServoMotorImpl _servo;
};