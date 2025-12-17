#pragma once

#include <Arduino.h>
#include "Task.hpp"
#include "LinkedList.h"
#include "Scheduler.hpp"

class Scheduler_Impl : public Scheduler
{
private:
    long period;
    LinkedList<Task *> queue;
    LinkedList<int> tasksToRemove;

    void removeTaskFromQueue();

public:
    Scheduler_Impl(long period) : period(period) {}
    ~Scheduler_Impl();

    void addTask(Task *t) override;
    void removeTask(int id) override;
    void excecuteTask() override;
    void clearQueue() override;
};