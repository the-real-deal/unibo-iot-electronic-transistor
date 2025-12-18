#include "TempSensorImpl.h"
#include "../kernel/Logger.h"
#include <Arduino.h>

TempSensorDHT11::TempSensorDHT11(int pin)
{
    this->dht = new DHT_Unified(pin, DHT11);
    this->pin = pin;
}

TempSensorDHT11::~TempSensorDHT11()
{
    delete dht;
}

float TempSensorDHT11::getTemperature()
{
    sensors_event_t event;
    dht->temperature().getEvent(&event);
    if (isnan(event.temperature))
    {
        Logger.log("Error reading temperature!");
    }
    else
    {
        return event.temperature;
    }
    /* Reading with different sensor */
    // int reading = analogRead(pin);
    // float voltage = reading * (5.0 / 1023.0);
    // float temperatureC = voltage * 100.0;
    // return temperatureC;
    // return 20.0;
}
