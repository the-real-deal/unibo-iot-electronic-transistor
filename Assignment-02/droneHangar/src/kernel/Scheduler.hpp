#pragma once

#include <Arduino.h>
#include <LinkedList.h>
#include "Task.hpp"
#include "devices/Led.h"

class Scheduler
{
private:
    long period;
    LinkedList<Task *> queue;
    LinkedList<int> tasksToRemove;
    Led builtIn;

    void removeTaskFromQueue();

public:
    Scheduler(long period);
    ~Scheduler();

    void addTask(Task *t);
    void removeTask(int id);
    void executeTask();
    void clearQueue();
};