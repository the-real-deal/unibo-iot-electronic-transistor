#pragma once
#include "model/states/Context.hpp"
#include "model/Timer.hpp"

class LandingState : public HangarState
{
private:
    HangarSubState currentSubState;
    Timer t;

public:
    LandingState(HWPlatform *platform, InputHolder *holder);
    ~LandingState() = default;
    void initializeTasks() override;
    String sendDRUData() override;
    String getStateInfo() override;
    void checkUpdate() override;
};