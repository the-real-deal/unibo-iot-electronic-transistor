#pragma once

#include <Arduino.h>
#include "Task.hpp"
#include "LinkedList.h"

class Scheduler_Impl
{
private:
    long period;
    LinkedList<Task *> queue;

public:
    Scheduler_Impl(long period) : period(period) {}
    ~Scheduler_Impl();

    void addTask(Task *t);
    void removeTask(int id);
    void excecuteTask();
    void clearQueue();
};