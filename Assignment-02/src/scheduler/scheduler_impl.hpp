#pragma once

#include "task.hpp"
#include "LinkedList.h"

class Scheduler_Impl
{
private:
    static const long period = 20;
    LinkedList<Task> queue;

public:
    Scheduler_Impl(/* args */);
    ~Scheduler_Impl();

    bool addTask(Task t);
    bool removeTask(int id);
    void excecuteTask();
    void clearQueue();
};