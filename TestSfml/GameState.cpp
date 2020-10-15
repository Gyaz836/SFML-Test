#include "GameState.h"

GameState::GameState(StateStack& stack, Context context)
    : State(stack, context)
    , mWorld(*context.window)
{

}

void GameState::draw()
{
    mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
    mPlayer.handleRealTimeInput(mWorld.getCommandQueue());
    mWorld.update(dt);

    return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::EventType::KeyPressed && event.key.code == sf::Keyboard::Key::Escape) {
        requestStackPush(States::ID::Pause);
    }

    mPlayer.handleEvent(event, mWorld.getCommandQueue());

    return true;
}
