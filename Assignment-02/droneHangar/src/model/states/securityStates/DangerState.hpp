#pragma once
#include "model/states/Context.hpp"

class DangerState : public SecurityState
{
private:
public:
    DangerState(HWPlatform *platform, InputHolder *holder);
    ~DangerState() = default;

    bool canReceiveMsg() override;
    void initializeTasks() override;
    void checkUpdate() override;
};