#pragma once
#include "model/states/Context.hpp"
#include <Arduino.h>

class IdleState : public HangarState
{
private:

public:
    IdleState(HWPlatform *platform, InputHolder *holder);
    ~IdleState() = default;
    void initializeTasks() override;
    String sendDRUData() override;
    String getStateInfo() override;
    void checkUpdate() override;
    void handleRequest(String msg) override;
};
