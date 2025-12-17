#pragma once
#include "HangarState.hpp"
#include <Arduino.h>

class StopState : public HangarState
{
private:
    /* data */
public:
    StopState(/* args */);
    ~StopState();

    void initializeTasks(HWPlatform *platform) override;
    String sendDRUData() override;
    String getStateInfo() override;
    void changeState() override;
};