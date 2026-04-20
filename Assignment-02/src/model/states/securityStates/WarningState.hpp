#pragma once
#include "model/states/Context.hpp"
#include "model/Timer.hpp"

class WarningState : public SecurityState
{
private:
    Timer t;

public:
    WarningState(HWPlatform *platform, InputHolder *holder);
    ~WarningState() = default;

    String sendDRUData() override;
    bool canReceiveMsg() override;
    void initializeTasks() override;
    void checkUpdate() override;
    String getStateInfo() override;
};
