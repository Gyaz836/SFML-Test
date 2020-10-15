#include "State.h"
#include "StateStack.h"

State::State(StateStack& stack, Context context)
    : mStack(&stack)
    , mContext(context)
{

}

State::~State() = default;

void State::requestStackPush(States::ID state)
{
    mStack->pushState(state);
}

void State::requestStackPop()
{
    mStack->popState();
}

void State::requestStackClear()
{
    mStack->clearStates();
}

State::Context State::getContext() const
{
    return mContext;
}

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player)
    : window(&window)
    , textures(&textures)
    , fonts(&fonts)
    , player(&player)
{}
