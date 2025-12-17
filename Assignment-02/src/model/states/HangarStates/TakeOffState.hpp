#pragma once
#include "HangarState.hpp"

class TakeOffState : public HangarState
{
private:
    /* data */
public:
    TakeOffState(/* args */);
    ~TakeOffState();

    void initializeTasks(HWPlatform *platform) override;
    String sendDRUData() override;
    String getStateInfo() override;
    void changeState() override;
};