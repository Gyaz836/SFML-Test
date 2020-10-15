#ifndef CommandQueue_h__
#define CommandQueue_h__

#include <queue>

#include "Command.h"

class CommandQueue
{
public:
    void push(const Command& command);
    Command pop();
    bool isEmpty() const;

private:
    std::queue<Command> mQueue;
};

#endif // CommandQueue_h__

