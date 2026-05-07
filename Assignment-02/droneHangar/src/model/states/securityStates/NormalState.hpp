#pragma once
#include "model/states/Context.hpp"
#include "model/Timer.hpp"

class NormalState : public SecurityState
{
private:
    Timer t;

public:
    NormalState(HWPlatform *platform, InputHolder *holder);
    ~NormalState() = default;

    bool canReceiveMsg() override;
    void initializeTasks() override;
    void checkUpdate() override;
};
