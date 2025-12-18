#pragma once
#include "../Context.hpp"

class DangerState : public SecurityState
{
private:
    int *taskAdded;

public:
    DangerState();
    ~DangerState();

    String sendDRUData() override;
    bool canReceiveMsg() override;
    void initializeTasks(HWPlatform *platform) override;
    void changeState() override;
    String getStateInfo() override;
};