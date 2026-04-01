#pragma once
#include "model/states/Context.hpp"

class DangerState : public SecurityState
{
private:
    int *taskAdded;

public:
    DangerState();
    ~DangerState();

    String sendDRUData() override;
    bool canReceiveMsg() override;
    void initializeTasks(HWPlatform *platform, InputHolder *holder) override;
    void checkUpdate() override;
    String getStateInfo() override;
};