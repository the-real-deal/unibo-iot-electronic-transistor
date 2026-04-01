#pragma once
#include "../Context.hpp"

class NormalState : public SecurityState
{
private:
    /* data */
public:
    NormalState(/* args */);
    ~NormalState();

    String sendDRUData() override;
    bool canReceiveMsg() override;
    void initializeTasks(HWPlatform *platform, InputHolder *holder) override;
    void checkUpdate() override;
    String getStateInfo() override;
};
