#pragma once
#include "HangarState.hpp"
#include <Arduino.h>

class IdleState : public HangarState
{
private:
    /* data */
public:
    IdleState(/* args */);
    ~IdleState();
    void initializeTasks(HWPlatform *platform) override;
    String sendDRUData() override;
    String getStateInfo() override;
    void changeState() override;
};
