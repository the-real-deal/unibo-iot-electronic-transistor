#pragma once

#include "model/states/Context.hpp"

class ButtonTask : public Task
{
private:
    Button *btn;
    Context *context;
    InputHolder *holder;
    ContextType type;

public:
    ButtonTask(Button *btn, Context *ctx, InputHolder *holder, ContextType type);
    ~ButtonTask() = default;
    void execute() override;
    void cleanup() override;
};