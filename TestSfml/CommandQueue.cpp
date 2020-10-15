#include "CommandQueue.h"

void CommandQueue::push(const Command& command)
{
    mQueue.push(command);
}

Command CommandQueue::pop()
{
    auto ret = mQueue.front();
    mQueue.pop();
    return ret;
}

bool CommandQueue::isEmpty() const
{
    return mQueue.empty();
}
