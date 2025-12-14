#pragma once
#include "SecurityState.hpp"

class WarningState : public SecurityState
{
private:
    /* data */
public:
    WarningState(/* args */);
    ~WarningState();

    char *sendDRUData() override;
    void recieveDRUData() override;
};
