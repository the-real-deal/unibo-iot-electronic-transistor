#pragma once
#include "../Context.hpp"

class LandingState : public HangarState
{
private:
    HangarSubState currentSubState;

public:
    LandingState(/* args */);
    ~LandingState();
    void initializeTasks(HWPlatform *platform) override;
    String sendDRUData() override;
    String getStateInfo() override;
    void checkUpdate() override;
};