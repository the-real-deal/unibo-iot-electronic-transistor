#pragma once
class ServoMotor
{

public:
    virtual ~ServoMotor() {};
    virtual void on() = 0;
    virtual void setPosition(int angle) = 0;
    virtual int getPosition() = 0;
    virtual void off() = 0;
};