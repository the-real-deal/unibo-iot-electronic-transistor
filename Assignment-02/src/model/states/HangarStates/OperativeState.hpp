#pragma once
#include "model/states/Context.hpp"
#include <Arduino.h>

class OperativeState : public HangarState
{
private:
    /* data */
public:
    OperativeState(HWPlatform *platform, InputHolder *holder);
    ~OperativeState() = default;
    void initializeTasks() override;
    String sendDRUData() override;
    String getStateInfo() override;
    void checkUpdate() override;
};
