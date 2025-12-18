#include "../Task.hpp"
#include "../../model/states/Context.hpp"

class exampleTask : public Task
{
private:
    Context *context;

public:
    exampleTask(Context *ctx);
    ~exampleTask();
    virtual void execute() override;
    virtual void cleanup() override;
};

exampleTask::exampleTask(Context *ctx) : context(ctx)
{
}

exampleTask::~exampleTask()
{
}

void exampleTask::execute()
{
    if (/* some condition */ false)
    {
        setCompleted();
    }
    if (/* some other condition */ false)
    {
        context->changeState("HGR");
    }
}

void exampleTask::cleanup()
{
    // Cleanup code goes here
}