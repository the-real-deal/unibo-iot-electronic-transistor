#include "TempSensorImpl.hpp"
#include "Arduino.h"

TempSensorDHT11::TempSensorDHT11(int pin) : pin(pin) {
   this->pin = pin;
}

float TempSensorDHT11::getTemperature() {
    int sensorValue = analogRead(pin);
    float voltage = sensorValue * (5.0 / 1023.0);
    float temperatureC = voltage * 100.0; // LM35 gives 10mV per degree Celsius
    return temperatureC;
}