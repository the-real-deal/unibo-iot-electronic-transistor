#pragma once

#include "task.hpp"
#include "LinkedList.h"

class Scheduler_Impl
{
private:
    static const long period = 20;
    LinkedList<Task> queue;
    int index;

public:
    Scheduler_Impl();
    ~Scheduler_Impl();

    void addTask(Task t);
    Task removeTask(int id);
    void excecuteTask();
    void clearQueue();
};