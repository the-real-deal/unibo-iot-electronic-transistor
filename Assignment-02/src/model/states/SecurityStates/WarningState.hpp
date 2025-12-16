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
    void recieveDRUData(String data) override;
    void initializeTasks(HWPlatform *platform) override;
    void changeState() override;
    String getStateInfo() override;
};
