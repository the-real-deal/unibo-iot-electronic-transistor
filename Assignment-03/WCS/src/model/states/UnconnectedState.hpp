#pragma once
#include "model/states/State.hpp"

class UnconnectedState : public State
{
public:
    void manageEvents() override;
};