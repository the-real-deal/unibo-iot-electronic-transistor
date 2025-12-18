#ifndef __TEMP_SENSOR__
#define __TEMP_SENSOR__

class TempSensor
{

public:
  virtual ~TempSensor() {}
  virtual float getTemperature() = 0;
};

#endif
