#ifndef Player_h__
#define Player_h__

#include <SFML/Window/Event.hpp>

#include "CommandQueue.h"
#include "Aircraft.h"

class Player
{
public:
    enum class Action
    {
        MoveUp,
        MoveDown,
        MoveRight,
        MoveLeft,

        Count
    };

    Player();

    void handleEvent(const sf::Event& event, CommandQueue& commQueue);
    void handleRealTimeInput(CommandQueue& commQueue);

    void setDefaultKeyBindings();
    void setDefaultKeyBinding(Action action);

    sf::Keyboard::Key getKeyBinding(Action action);
    void setKeyBinding(Action action, sf::Keyboard::Key key);

private:
    static bool isRealTimeAction(Action action);

    void bindCommands();

    std::map<sf::Keyboard::Key, Action> mKeyBinding;
    std::map<Action, Command> mActionBinding;
    float mPlayerSpeed = 300.f;
};

#endif // Player_h__

