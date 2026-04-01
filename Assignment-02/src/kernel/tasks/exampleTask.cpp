#include "kernel/Task.hpp"
#include "model/states/Context.hpp"

class exampleTask : public Task
{
private:
    Context *context;
    ContextType type;
public:
    exampleTask(Context *ctx, ContextType ctxType);
    virtual ~exampleTask();
    void execute() override;
    void cleanup() override;
};

exampleTask::exampleTask(Context *ctx, ContextType ctxType) : context(ctx), type(ctxType) {}

exampleTask::~exampleTask()
{
}

void exampleTask::execute()
{
    if (/* some condition */ false)
    {
        setCompleted();
    }

    this->context->checkUpdate(this->type);
}

void exampleTask::cleanup()
{
    // Cleanup code goes here
}