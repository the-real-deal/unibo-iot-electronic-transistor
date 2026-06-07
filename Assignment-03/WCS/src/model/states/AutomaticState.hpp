#pragma once
#include "model/states/State.hpp"

class AutomaticState : public State
{
public:
    ~AutomaticState() = default;

    void manageEvents() override;
};
