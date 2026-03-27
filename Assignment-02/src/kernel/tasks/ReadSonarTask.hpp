#pragma once

#include "../Task.hpp"
#include "../../devices/Sonar.h"

class ReadSonarTask : public Task
{

private:
    Sonar *sonar;
    // [TODO] Add input values holder

public:
    ReadSonarTask(Sonar *sonar);
    virtual ~ReadSonarTask() = default;

    void execute() override;
    void cleanup() override;
};