#pragma once
#include "model/states/Context.hpp"
#include "LinkedList.h"
#include <Arduino.h>

class IdleState : public HangarState
{
private:
    /* data */
public:
    IdleState(/* args */);
    ~IdleState();
    void initializeTasks(HWPlatform *platform, InputHolder *holder) override;
    String sendDRUData() override;
    String getStateInfo() override;
    void checkUpdate() override;
};
