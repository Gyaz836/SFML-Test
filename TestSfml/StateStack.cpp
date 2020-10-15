#include "StateStack.h"

#include <assert.h>

StateStack::StateStack(State::Context context)
    : mContext(context)
{

}

void StateStack::update(sf::Time dt)
{
    for (auto stateIt = mStack.rbegin(); stateIt != mStack.rend(); ++stateIt) {
        if (!(*stateIt)->update(dt)) {
            break;
        }
    }

    applyPendingChanges();
}

void StateStack::draw()
{
    for (auto& state : mStack) {
        state->draw();
    }
}

void StateStack::handleEvent(const sf::Event& event)
{
    for (auto stateIt = mStack.rbegin(); stateIt != mStack.rend(); ++stateIt) {
        if (!(*stateIt)->handleEvent(event)) {
            break;
        }
    }

    applyPendingChanges();
}

void StateStack::pushState(States::ID state)
{
    mPendingList.push_back({ Action::Push, state });
}

void StateStack::popState()
{
    mPendingList.push_back({ Action::Pop, States::ID::None });
}

void StateStack::clearStates()
{
    mPendingList.push_back({ Action::Clear, States::ID::None });
}

bool StateStack::isEmpty() const
{
    return mStack.empty();
}

State::Ptr StateStack::createState(States::ID state)
{
    auto factoryIt = mFactories.find(state);

    assert(factoryIt != mFactories.end());
    assert(factoryIt->second);

    return factoryIt->second();
}

void StateStack::applyPendingChanges()
{
    for (auto& change : mPendingList) {
        switch (change.action)
        {
        case Action::Push:
            mStack.push_back(createState(change.state));
            break;
        case Action::Pop:
            mStack.pop_back();
            break;
        case Action::Clear:
            mStack.clear();
            break;
        }
    }

    mPendingList.clear();
}
