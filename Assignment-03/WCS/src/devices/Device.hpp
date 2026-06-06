#pragma once

class Device
{
private:
public:
    ~Device() = default;

    /**
     * Initializes the device pins
     */
    virtual void init() = 0;
};