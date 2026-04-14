#pragma once
#include "model/states/Context.hpp"

class DangerState : public SecurityState
{
private:
    int *taskAdded;

public:
    DangerState(HWPlatform *platform, InputHolder *holder);
    ~DangerState() = default;

    String sendDRUData() override;
    bool canReceiveMsg() override;
    void initializeTasks() override;
    void checkUpdate() override;
    String getStateInfo() override;
};