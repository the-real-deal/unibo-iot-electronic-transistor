#pragma once
#include "../Context.hpp"
#include <Arduino.h>

class OperativeState : public HangarState
{
private:
    /* data */
public:
    OperativeState(/* args */);
    ~OperativeState();
    void initializeTasks(HWPlatform *platform) override;
    String sendDRUData() override;
    String getStateInfo() override;
    void changeState() override;
};
