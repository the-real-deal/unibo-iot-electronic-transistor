#include "ButtonTask.hpp"
// #include "model/messageManager/Logger.h"

ButtonTask::ButtonTask(Button *btn, Context *ctx, InputHolder *holder, ContextType type) : btn(btn),
                                                                                           context(ctx),
                                                                                           holder(holder),
                                                                                           type(type) {}

void ButtonTask::cleanup()
{
    this->holder->setIsPressed(false);
}

void ButtonTask::execute()
{
    // Logger.log(String(this->btn->isPressed()));
    this->holder->setIsPressed(this->btn->isPressed());
    this->context->checkUpdate(type);
}