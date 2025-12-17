#pragma once
#include "HangarState.hpp"

class LandingState : public HangarState
{
private:
    /* data */
public:
    LandingState(/* args */);
    ~LandingState();
    void initializeTasks(HWPlatform *platform) override;
    String sendDRUData() override;
    String getStateInfo() override;
    void changeState() override;
};