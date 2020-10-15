#ifndef State_h__
#define State_h__

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "ResourceHolder.h"
#include "Player.h"
#include "StateDefinitions.h"

class StateStack;

class State
{
public:
    using Ptr = std::unique_ptr<State>;

    struct Context
    {
        Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player);
        sf::RenderWindow* window;
        TextureHolder* textures;
        FontHolder* fonts;
        Player* player;
    };

    State(StateStack& stack, Context context);
    virtual ~State();

    virtual void draw() = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

protected:
    void requestStackPush(States::ID state);
    void requestStackPop();
    void requestStackClear();

    Context getContext() const;

private:
    StateStack* mStack = nullptr;
    Context mContext;
};

#endif // State_h__
