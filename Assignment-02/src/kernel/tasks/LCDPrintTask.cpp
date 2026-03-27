#include "LCDPrintTask.hpp"

LCDPrintTask::LCDPrintTask(LCD *lcd, String ttd) : lcd(lcd), text(ttd) {}

void LCDPrintTask::execute()
{
    lcd->print(1, text);
    setCompleted();
}

void LCDPrintTask::cleanup()
{
}
