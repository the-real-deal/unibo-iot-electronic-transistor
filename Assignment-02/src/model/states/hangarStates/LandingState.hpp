#pragma once
#include "model/states/Context.hpp"
#include "model/Timer.hpp"

class LandingState : public HangarState
{
private:
    HangarSubState currentSubState;
    Timer t;
    int blinkTaskId;

public:
    LandingState(HWPlatform *platform, InputHolder *holder);
    ~LandingState() = default;
    void initializeTasks() override;
    void checkUpdate() override;
};