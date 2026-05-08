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

    void setTemperature(float temp);
    void setDistance(float dist);
    void setMotionDetected(bool detected);
    void setMessage(String msg);
    void setIsPressed(bool pressed);

    float getTemperature();
    float getDistance();
    bool isMotionDetected();
    String getMessage();
    bool isPressed();
};
