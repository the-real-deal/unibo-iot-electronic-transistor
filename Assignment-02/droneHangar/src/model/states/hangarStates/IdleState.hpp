#pragma once
#include "model/states/Context.hpp"
#include <Arduino.h>

class IdleState : public HangarState
{
private:
public:
    IdleState(HWPlatform *platform, InputHolder *holder);
    ~IdleState() = default;
    void initializeTasks() override;
    void checkUpdate() override;
};
