#pragma once
#include "model/states/Context.hpp"
#include <Arduino.h>

class StopState : public HangarState
{
private:
    bool isIn;

public:
    StopState(HWPlatform *platform, InputHolder *holder);
    ~StopState() = default;

    void initializeTasks() override;
    String sendDRUData() override;
    String getStateInfo() override;
    void checkUpdate() override;
};