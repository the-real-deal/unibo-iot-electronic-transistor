#ifndef __TEMP_SENSOR_LM35__
#define __TEMP_SENSOR_LM35__

#include "TempSensor.h"


class TempSensorDHT11 : public TempSensor {

  private:
    int pin;

  public:
    TempSensorDHT11(int pin) : pin(pin) {}
    virtual float getTemperature();
};

/*
class TempSensorLM35: public TempSensor {

public:
  TempSensorLM35(int pin);	
  virtual float getTemperature();
  
private:
  int pin;
};*/


#endif

