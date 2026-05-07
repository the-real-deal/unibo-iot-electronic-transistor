#pragma once

#include <WString.h>

class InputHolder
{
private:
    float temperature;
    float distance;
    bool motionDetected;
    String message;
    bool pressed;

public:
    InputHolder();
    ~InputHolder();

    virtual void setTemperature(float temp) = 0;
    virtual void setDistance(float dist) = 0;
    virtual void setMotionDetected(bool detected) = 0;
    virtual void setMessage(String msg) = 0;
    virtual void setIsPressed(bool pressed) = 0;

    virtual float getTemperature() = 0;
    virtual float getDistance() = 0;
    virtual bool isMotionDetected() = 0;
    virtual String getMessage() = 0;
    virtual bool isPressed() = 0;
};
