#ifndef __BUTTON__
#define __BUTTON__

class Button
{

public:
  virtual ~Button() {};
  virtual bool isPressed() = 0;
};

#endif
