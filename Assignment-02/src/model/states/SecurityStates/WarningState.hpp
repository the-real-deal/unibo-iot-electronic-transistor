#pragma once
#include "SecurityState.hpp"

class WarningState : public SecurityState
{
private:
    /* data */
public:
    WarningState(/* args */);
    ~WarningState();

    String sendDRUData() override;
    bool canReceiveMsg() override;
    void initializeTasks(HWPlatform *platform) override;
    void changeState() override;
    String getStateInfo() override;
};
