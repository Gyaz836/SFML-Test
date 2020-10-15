#ifndef MenuState_h__
#define MenuState_h__

#include "State.h"

class MenuState : public State
{
public:
    MenuState(StateStack& stack, Context context);

    void draw() override;

    bool update(sf::Time dt) override;

    bool handleEvent(const sf::Event& event) override;

private:
    enum class MenuEntries
    {
        Play,
        Settings,
        Exit,

        Count
    };
};

#endif // MenuState_h__

