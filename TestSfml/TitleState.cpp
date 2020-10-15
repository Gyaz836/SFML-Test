#include "TitleState.h"

TitleState::TitleState(StateStack& stack, Context context)
    : State(stack, context)
{
    loadTextures();
    loadFonts();
    mText.setFont(getContext().fonts->get(Fonts::ID::Sansation));
    mText.setString("Press any key to continue");
    auto windowSize = getContext().window->getSize();
    mText.setPosition(windowSize.x / 2 - (mText.getLocalBounds().width / 2), windowSize.y - (mText.getLocalBounds().height / 2) - 50);

    mBackgroundSprite.setTexture(getContext().textures->get(Textures::ID::TitleBackground));
}

void TitleState::draw()
{
    getContext().window->draw(mBackgroundSprite);
    if (mShowText)
        getContext().window->draw(mText);
}

bool TitleState::update(sf::Time dt)
{
    mTextEffectTime += dt;

    if (mTextEffectTime.asSeconds() > 0.5f) {
        mShowText = !mShowText;

        mTextEffectTime = sf::Time::Zero;
    }

    return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::ID::Menu);
    }

    return true;
}

void TitleState::loadTextures()
{
    getContext().textures->load(Textures::ID::TitleBackground, "Resources/Textures/TitleScreen.png");
}

void TitleState::loadFonts()
{
    getContext().fonts->load(Fonts::ID::Sansation, "Resources/Fonts/Sansation.ttf");
}
