#include "ButtonTask.hpp"

ButtonTask::ButtonTask(Button *btn, Context *ctx, InputHolder *holder, ContextType type) : btn(btn), context(ctx), holder(holder), type(type) {}

void ButtonTask::cleanup() {}

void ButtonTask::execute()
{
    this->holder->setIsPressed(this->btn->isPressed());
    this->context->checkUpdate(type);
}