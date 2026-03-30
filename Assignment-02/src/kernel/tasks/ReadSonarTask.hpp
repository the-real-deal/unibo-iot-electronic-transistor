#pragma once

#include "../Task.hpp"
#include "../../devices/Sonar.h"
#include "../../model/states/Context.hpp"
#include "../../model/InputHolder.hpp"

class ReadSonarTask : public Task
{

private:
    Sonar *sonar;
    Context *context;
    InputHolder *holder;
public:
    ReadSonarTask(Sonar *sonar, Context* ctx, InputHolder *valHolder);
    virtual ~ReadSonarTask() = default;

    void execute() override;
    void cleanup() override;
};