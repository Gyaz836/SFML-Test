#ifndef Game_h__
#define Game_h__

#include <memory>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "SFML/Graphics/Sprite.hpp"

#include "ResourceHolder.h"
#include "Aircraft.h"
#include "World.h"

namespace sf {
    class RenderWindow;
}

class Game
{
public:
    Game();
    virtual ~Game();

    void run();
private:
    sf::Clock deltaClock;
    sf::Time fullFrameDeltaTime;
    sf::Time timePerFrame = sf::seconds(1.f / 60.f);

    void updateDeltaTime();
    void updateSFMLEvents();
    void update(sf::Time dt);
    void render();

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    bool consoleOpened = false;
    bool consoleReleased = true;
    bool settingsOpened = false;

    std::unique_ptr<sf::RenderWindow> window;
    sf::Event sfEvent{};

    World mWorld;
};

#endif // Game_h__
