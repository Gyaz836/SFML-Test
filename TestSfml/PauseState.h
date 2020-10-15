#ifndef PauseState_h__
#define PauseState_h__

#include "State.h"

class PauseState : public State
{
public:
    PauseState(StateStack& stack, Context context);

    void draw() override;

    bool update(sf::Time dt) override;

    bool handleEvent(const sf::Event& event) override;

};

#endif // PauseState_h__

