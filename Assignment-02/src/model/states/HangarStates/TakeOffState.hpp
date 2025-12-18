#pragma once
#include "../Context.hpp"

class TakeOffState : public HangarState
{
private:
    HangarSubState currentSubState;

public:
    TakeOffState(/* args */);
    ~TakeOffState();

    void initializeTasks(HWPlatform *platform) override;
    String sendDRUData() override;
    String getStateInfo() override;
    void changeState() override;
};