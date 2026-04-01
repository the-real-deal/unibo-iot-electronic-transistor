#pragma once
#include "model/states/Context.hpp"
#include <Arduino.h>

class StopState : public HangarState
{
private:
    bool isIn;

public:
    StopState(/* args */);
    ~StopState();

    void initializeTasks(HWPlatform *platform, InputHolder *holder) override;
    String sendDRUData() override;
    String getStateInfo() override;
    void checkUpdate() override;
};