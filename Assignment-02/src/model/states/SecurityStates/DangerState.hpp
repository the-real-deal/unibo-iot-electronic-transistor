#pragma once
#include "SecurityState.hpp"

class DangerState : public SecurityState
{
private:
    int *taskAdded;

public:
    DangerState();
    ~DangerState()
    {
        delete taskAdded;
    }

    String sendDRUData() override;
    void recieveDRUData(String data) override;
    void initializeTasks(HWPlatform *platform) override;
    void changeState() override;
    String getStateInfo() override;
};