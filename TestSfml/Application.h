#ifndef Application_h__
#define Application_h__

#include "StateStack.h"

class Application : private sf::NonCopyable
{
public:
    Application();
    virtual ~Application();

    void run();
private:
    sf::Clock deltaClock;
    sf::Time fullFrameDeltaTime;
    sf::Time timePerFrame = sf::seconds(1.f / 60.f);

    void updateDeltaTime();

    void processInput();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time dt);
    void draw();

    void registerStates();

    bool consoleOpened = false;
    bool consoleReleased = true;
    bool settingsOpened = false;

    std::unique_ptr<sf::RenderWindow> mWindow;
    TextureHolder mTextures;
    FontHolder mFonts;
    std::unique_ptr<Player> mPlayer;
    State::Context mContext;
    StateStack mStateStack;
};

#endif // Application_h__

