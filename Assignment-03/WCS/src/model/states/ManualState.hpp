#pragma once
#include "model/states/State.hpp"

class ManualState : public State
{
public:
    void manageEvents() override;
};
