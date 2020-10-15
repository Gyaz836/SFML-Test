#ifndef SettingsState_h__
#define SettingsState_h__

#include "State.h"

class SettingsState : public State
{
public:
    SettingsState(StateStack& stack, Context context);

    void draw() override;

    bool update(sf::Time dt) override;

    bool handleEvent(const sf::Event& event) override;

private:

};

#endif // SettingsState_h__

