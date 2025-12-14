#pragma once
#include "SecurityState.hpp"

class DangerState : public SecurityState
{
private:
    /* data */
public:
    DangerState(/* args */);
    ~DangerState();

    char *sendDRUData() override;
    void recieveDRUData() override;
};