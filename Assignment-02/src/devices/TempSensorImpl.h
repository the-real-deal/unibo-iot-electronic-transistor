#ifndef __TEMP_SENSOR_LM35__
#define __TEMP_SENSOR_LM35__

#include "TempSensor.h"
#include "DHT.h"
#include "config.h"

class TempSensorDHT11 : public TempSensor
{

public:
  TempSensorDHT11();
  TempSensorDHT11(int pin);
  ~TempSensorDHT11() override;
  virtual float getTemperature();

private:
  DHT dht;
  int pin;
};

#endif
