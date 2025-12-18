#pragma once

#include <Arduino.h>
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
    Scheduler_Impl(long period);
    ~Scheduler_Impl() override;

    void addTask(Task *t) override;
    void removeTask(int id) override;
    void executeTask() override;
    void clearQueue() override;
};