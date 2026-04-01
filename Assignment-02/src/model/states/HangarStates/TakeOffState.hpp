#pragma once
#include "model/states/Context.hpp"

class TakeOffState : public HangarState
{
private:
    HangarSubState currentSubState;

public:
    TakeOffState(/* args */);
    ~TakeOffState();

    void initializeTasks(HWPlatform *platform, InputHolder *holder) override;
    String sendDRUData() override;
    String getStateInfo() override;
    void checkUpdate() override;
};