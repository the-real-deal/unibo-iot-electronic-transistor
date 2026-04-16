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
    HWPlatform() : _button(new ButtonImpl(BUTTON1)),
                   _led2(new Led(LED2)),
                   _led3(new Led(LED3)),
                   _pir(new Pir(PIR_PIN)),
                   _lcd(new LCD(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS)),
                   _distanceDetector(new Sonar(SONAR_ECHO_PIN, SONAR_TRIG_PIN, 30000)),
                   _temperatureSensor(new TempSensorDHT11(DHTPIN)),
                   _servo(new ServoMotorImpl(SERVO_PIN)) {};

    ~HWPlatform()
    {
        delete _button;
        delete _led2;
        delete _led3;
        delete _pir;
        delete _lcd;
        delete _distanceDetector;
        delete _temperatureSensor;
        delete _servo;
    };

    Button *getButton()
    {
        return this->_button;
    };

    Led *getLed2()
    {
        return this->_led2;
    }

    Led *getLed3()
    {
        return this->_led3;
    }

    PresenceSensor *getPIR()
    {
        return this->_pir;
    }

    LCD *getLCD()
    {
        return this->_lcd;
    }

    ProximitySensor *getDistanceDetector()
    {
        return this->_distanceDetector;
    }

    TempSensor *getTemperatureSensor()
    {
        return this->_temperatureSensor;
    }

    ServoMotor *getServoMotor()
    {
        return this->_servo;
    }
private:
    Button *_button;
    Led *_led2;
    Led *_led3;
    PresenceSensor *_pir;
    LCD *_lcd;
    ProximitySensor *_distanceDetector;
    TempSensor *_temperatureSensor;
    ServoMotor* _servo;
};