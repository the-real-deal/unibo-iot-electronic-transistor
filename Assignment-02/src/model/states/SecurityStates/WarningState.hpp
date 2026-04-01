#pragma once
#include "model/states/Context.hpp"

class WarningState : public SecurityState
{
private:
    /* data */
public:
    WarningState(/* args */);
    ~WarningState();

    String sendDRUData() override;
    bool canReceiveMsg() override;
    void initializeTasks(HWPlatform *platform, InputHolder *holder) override;
    void checkUpdate() override;
    String getStateInfo() override;
};
