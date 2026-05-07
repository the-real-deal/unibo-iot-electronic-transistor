#ifndef __PROXIMITYSENSOR__
#define __PROXIMITYSENSOR__

class ProximitySensor
{

public:
  virtual ~ProximitySensor() {}
  virtual float getDistance() = 0;
};

#endif
