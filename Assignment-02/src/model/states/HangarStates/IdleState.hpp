#pragma once
#include "../Context.hpp"
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
    void checkUpdate() override;
};
