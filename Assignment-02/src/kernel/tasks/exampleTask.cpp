#include "../Task.hpp"
#include "../../model/states/Context.hpp"

class exampleTask : public Task
{
private:
    Context *context;

public:
    exampleTask(Context *ctx);
    ~exampleTask();
    virtual void excecute() override;
    virtual void cleanup() override;
};

exampleTask::exampleTask(Context *ctx) : context(ctx)
{
}

exampleTask::~exampleTask()
{
}

void exampleTask::excecute()
{
    if (/* some condition */ false)
    {
        setCompleted();
    }
    if (/* some other condition */ false)
    {
        context->setHangarState(new HangarState());
    }
}

void exampleTask::cleanup()
{
    // Cleanup code goes here
}