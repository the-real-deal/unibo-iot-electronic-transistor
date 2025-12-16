#pragma once
#include "SecurityState.hpp"

class NormalState : public SecurityState
{
private:
    /* data */
public:
    NormalState(/* args */);
    ~NormalState();

    String sendDRUData() override;
    void recieveDRUData(String data) override;
    void initializeTasks(HWPlatform *platform) override;
    void changeState() override;
    String getStateInfo() override;
};
