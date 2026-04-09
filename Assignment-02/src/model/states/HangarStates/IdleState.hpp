#pragma once
#include "model/states/Context.hpp"
#include <Arduino.h>

class IdleState : public HangarState
{
private:

public:
    IdleState(/* args */);
    ~IdleState();
    void initializeTasks(HWPlatform *platform, InputHolder *holder) override;
    String sendDRUData() override;
    String getStateInfo() override;
    void checkUpdate() override;
    void handleRequest(String msg) override;
};
