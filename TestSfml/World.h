#ifndef World_h__
#define World_h__

#include <array>
#include <SFML/Graphics/RenderWindow.hpp>

#include "ResourceHolder.h"
#include "SceneNode.h"
#include "Aircraft.h"
#include "CommandQueue.h"

class World
{
public:
    World(sf::RenderWindow& window);
    void update(sf::Time dt);
    void draw();

    CommandQueue& getCommandQueue();

private:
    enum class SceneLayer : int
    {
        Background,
        Air,

        Count,
    };

    void loadTextures();
    void buildScene();

private:
    sf::RenderWindow& mWindow;
    sf::View mWorldView;
    TextureHolder mTextures;
    SceneNode mSceneGraph;
    std::array<SceneNode*, static_cast<size_t>(SceneLayer::Count)> mSceneLayers;
    CommandQueue mCommandQueue;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    float mPlayerSpeed = 300.f;
    float mScrollSpeed = -80.f;
    Aircraft* mPlayerAircraft = nullptr;
};

#endif // World_h__

