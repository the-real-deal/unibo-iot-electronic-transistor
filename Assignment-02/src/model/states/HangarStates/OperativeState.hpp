#pragma once
#include "model/states/Context.hpp"
#include <Arduino.h>

class OperativeState : public HangarState
{
private:
    /* data */
public:
    OperativeState(/* args */);
    ~OperativeState();
    void initializeTasks(HWPlatform *platform, InputHolder *holder) override;
    String sendDRUData() override;
    String getStateInfo() override;
    void checkUpdate() override;
};
