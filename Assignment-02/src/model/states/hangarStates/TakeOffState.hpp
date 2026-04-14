#pragma once
#include "model/states/Context.hpp"

class TakeOffState : public HangarState
{
private:
    HangarSubState currentSubState;

public:
    TakeOffState(HWPlatform *platform, InputHolder *holder);
    ~TakeOffState() = default;

    void initializeTasks() override;
    String sendDRUData() override;
    String getStateInfo() override;
    void checkUpdate() override;
};