#ifndef __PRESENCE__
#define __PRESENCE__

class PresenceSensor
{

public:
  virtual ~PresenceSensor() {}
  virtual bool isDetected() = 0;
};

#endif
