#include "Player.h"

#include <iostream>

struct AircraftMover
{
    AircraftMover(float vx, float vy)
        : velocity(vx, vy)
    {}

    void operator() (SceneNode& node, sf::Time) const
    {
        auto& aircraft = static_cast<Aircraft&>(node);
        aircraft.accelerate(velocity);
    }

    sf::Vector2f velocity;
};

Player::Player()
{
    setDefaultKeyBindings();
    bindCommands();
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commQueue)
{
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::P)
    {
        Command printPos;
        printPos.category = Category::Type::PlayerAircrarft;
        printPos.action = [](SceneNode& node, sf::Time) {
            std::cout << node.getPosition().x << ", " << node.getPosition().y << "\n";
        };

        commQueue.push(printPos);
    }
}

void Player::handleRealTimeInput(CommandQueue& commQueue)
{
    for (auto& pair : mKeyBinding) {
        if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second)) {
            commQueue.push(mActionBinding[pair.second]);
        }
    }
}

void Player::setDefaultKeyBindings()
{
    for (size_t actionEnum = 0; actionEnum < static_cast<size_t>(Action::Count); ++actionEnum)
    {
        setDefaultKeyBinding(static_cast<Action>(actionEnum));
    }
}

void Player::setDefaultKeyBinding(Action action)
{
    switch (action)
    {
    case Player::Action::MoveUp:
        mKeyBinding[sf::Keyboard::Key::W] = action;
        break;
    case Player::Action::MoveDown:
        mKeyBinding[sf::Keyboard::Key::S] = action;
        break;
    case Player::Action::MoveRight:
        mKeyBinding[sf::Keyboard::Key::D] = action;
        break;
    case Player::Action::MoveLeft:
        mKeyBinding[sf::Keyboard::Key::A] = action;
        break;
    case Player::Action::Count:
        break;
    }
}

sf::Keyboard::Key Player::getKeyBinding(Action action)
{
    auto foundKeyIt = std::find_if(mKeyBinding.begin(), mKeyBinding.end(),
        [action](std::pair<sf::Keyboard::Key, Action> item)
        {
            if (item.second == action) {
                return true;
            }
            else {
                return false;
            }
        }
    );
    assert(foundKeyIt != mKeyBinding.end());
    return foundKeyIt->first;
}

void Player::setKeyBinding(Action action, sf::Keyboard::Key key)
{
    mKeyBinding[key] = action;
}

bool Player::isRealTimeAction(Action action)
{
    switch (action)
    {
    case Player::Action::MoveUp:
    case Player::Action::MoveDown:
    case Player::Action::MoveRight:
    case Player::Action::MoveLeft:
        return true;
    case Player::Action::Count:
        return false;
    }
    return false;
}

void Player::bindCommands()
{
    {
        Command moveUp;
        moveUp.category = Category::Type::PlayerAircrarft;
        moveUp.action = AircraftMover(0.f, -mPlayerSpeed);
        mActionBinding[Action::MoveUp] = std::move(moveUp);
    }
    {
        Command moveDown;
        moveDown.category = Category::Type::PlayerAircrarft;
        moveDown.action = AircraftMover(0.f, mPlayerSpeed);
        mActionBinding[Action::MoveDown] = std::move(moveDown);
    }
    {
        Command moveLeft;
        moveLeft.category = Category::Type::PlayerAircrarft;
        moveLeft.action = AircraftMover(-mPlayerSpeed, 0.f);
        mActionBinding[Action::MoveLeft] = std::move(moveLeft);
    }
    {
        Command moveRight;
        moveRight.category = Category::Type::PlayerAircrarft;
        moveRight.action = AircraftMover(mPlayerSpeed, 0.f);
        mActionBinding[Action::MoveRight] = std::move(moveRight);
    }
}
