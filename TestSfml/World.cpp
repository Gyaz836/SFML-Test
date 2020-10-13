#include "World.h"
#include "SpriteNode.h"

World::World(sf::RenderWindow& window)
    : mWindow(window)
    , mWorldView(window.getDefaultView())
    , mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 4000.f)
    , mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y)
    , mPlayerAircraft(nullptr)
{
    loadTextures();
    buildScene();

    mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
    mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

    sf::Vector2f position = mPlayerAircraft->getPosition();
    sf::Vector2f velocity = mPlayerAircraft->getVelocity();

    if (position.x <= mWorldBounds.left + 150 ||
        position.x >= mWorldBounds.left + mWorldBounds.width - 150)
    {
        velocity.x = -velocity.x;
        mPlayerAircraft->setVelocity(velocity);
    }

    mSceneGraph.update(dt);
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::loadTextures()
{
    mTextures.load(Textures::ID::Desert, "Textures/Desert.png");
    mTextures.load(Textures::ID::Eagle, "Textures/Eagle.png");
    mTextures.load(Textures::ID::Raptor, "Textures/Raptor.png");
}

void World::buildScene()
{
    for (size_t i = 0; i < static_cast<size_t>(SceneLayer::Count); ++i)
    {
        SceneNode::Ptr layer = std::make_unique<SceneNode>();
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    auto& desertTexture = mTextures.get(Textures::ID::Desert);
    sf::IntRect desertRect(mWorldBounds);
    desertTexture.setRepeated(true);

    SpriteNode::Ptr backgroundSprite = std::make_unique<SpriteNode>(desertTexture, desertRect);
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[static_cast<size_t>(SceneLayer::Background)]->attachChild(std::move(backgroundSprite));

    Aircraft::Ptr leader = std::make_unique<Aircraft>(Aircraft::Type::Eagle, mTextures);
    mPlayerAircraft = leader.get();
    mPlayerAircraft->setPosition(mSpawnPosition);
    mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
    mSceneLayers[static_cast<size_t>(SceneLayer::Air)]->attachChild(std::move(leader));

    Aircraft::Ptr leftEscort = std::make_unique<Aircraft>(Aircraft::Type::Raptor, mTextures);
    leftEscort->setPosition(-80.f, 50.f);
    mPlayerAircraft->attachChild(std::move(leftEscort));

    Aircraft::Ptr rightEscort = std::make_unique<Aircraft>(Aircraft::Type::Raptor, mTextures);
    rightEscort->setPosition(80.f, 50.f);
    mPlayerAircraft->attachChild(std::move(rightEscort));
}
