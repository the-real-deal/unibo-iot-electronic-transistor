#pragma once
#include "model/states/Context.hpp"
#include "model/Timer.hpp"

class TakeOffState : public HangarState
{
private:
    HangarSubState currentSubState;
    Timer t;

public:
    TakeOffState(HWPlatform *platform, InputHolder *holder);
    ~TakeOffState() = default;

    void initializeTasks() override;
    void checkUpdate() override;
};