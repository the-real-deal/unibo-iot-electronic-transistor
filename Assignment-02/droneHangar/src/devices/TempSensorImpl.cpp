#include "TempSensorImpl.h"
// #include "../kernel/Logger.h"

TempSensorDHT11::TempSensorDHT11() : dht(DHTPIN, DHT11), pin(0)
{
}

TempSensorDHT11::TempSensorDHT11(int pin) : dht(pin, DHT11), pin(pin)
{
    this->dht.begin();
}

TempSensorDHT11::~TempSensorDHT11()
{
}

float TempSensorDHT11::getTemperature()
{
    float temp = this->dht.readTemperature();
    if (isnan(temp))
    {
        return 20.0;
    }
    return temp;
}
