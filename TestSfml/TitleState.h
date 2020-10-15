#ifndef TitleState_h__
#define TitleState_h__

#include "State.h"
#include <SFML/Graphics/Text.hpp>

class TitleState : public State
{
public:
    TitleState(StateStack& stack, Context context);

    void draw() override;

    bool update(sf::Time dt) override;

    bool handleEvent(const sf::Event& event) override;

private:
    void loadTextures();
    void loadFonts();

    sf::Sprite mBackgroundSprite;
    sf::Text mText;

    bool mShowText = true;
    sf::Time mTextEffectTime = sf::Time::Zero;
};

#endif // TitleState_h__

