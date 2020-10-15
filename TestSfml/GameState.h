#ifndef GameState_h__
#define GameState_h__

#include "State.h"

#include "Player.h"
#include "World.h"

class GameState : public State
{
public:
    GameState(StateStack& stack, Context context);

    void draw() override;

    bool update(sf::Time dt) override;

    bool handleEvent(const sf::Event& event) override;

private:
    bool gamePaused = false;

    Player mPlayer;

    World mWorld;

};

#endif // GameState_h__

