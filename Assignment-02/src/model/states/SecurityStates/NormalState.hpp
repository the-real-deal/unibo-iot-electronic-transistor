#pragma once
#include "model/states/Context.hpp"

class NormalState : public SecurityState
{
private:
    /* data */
public:
    NormalState(HWPlatform *platform, InputHolder *holder);
    ~NormalState() = default;

    String sendDRUData() override;
    bool canReceiveMsg() override;
    void initializeTasks() override;
    void checkUpdate() override;
    String getStateInfo() override;
};
