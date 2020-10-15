#include "World.h"
#include "SpriteNode.h"
#include "SFML/Window/Keyboard.hpp"

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
    mPlayerAircraft->setVelocity(0.f, 0.f);

    while (!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);

    sf::Vector2f velocity = mPlayerAircraft->getVelocity();

    if (velocity.x != 0.f && velocity.y != 0.f)
    {
        mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));
    }

    mPlayerAircraft->accelerate({ 0.f, mScrollSpeed });

    sf::FloatRect viewBounds(
        mWorldView.getCenter() - mWorldView.getSize() / 2.f,
        mWorldView.getSize());
    const float borderDistance = 40.f;
    sf::Vector2f position = mPlayerAircraft->getPosition();
    position.x = std::max(position.x,
        viewBounds.left + borderDistance);
    position.x = std::min(position.x,
        viewBounds.left + viewBounds.width - borderDistance);
    position.y = std::max(position.y,
        viewBounds.top + borderDistance);
    position.y = std::min(position.y,
        viewBounds.top + viewBounds.height - borderDistance);
    mPlayerAircraft->setPosition(position);

    mSceneGraph.update(dt);
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

void World::loadTextures()
{
    mTextures.load(Textures::ID::Desert, "Resources/Textures/Desert.png");
    mTextures.load(Textures::ID::Eagle, "Resources/Textures/Eagle.png");
    mTextures.load(Textures::ID::Raptor, "Resources/Textures/Raptor.png");
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
    mPlayerAircraft->setVelocity(0, mScrollSpeed);
    mSceneLayers[static_cast<size_t>(SceneLayer::Air)]->attachChild(std::move(leader));

    Aircraft::Ptr leftEscort = std::make_unique<Aircraft>(Aircraft::Type::Raptor, mTextures);
    leftEscort->setPosition(-80.f, 50.f);
    mPlayerAircraft->attachChild(std::move(leftEscort));

    Aircraft::Ptr rightEscort = std::make_unique<Aircraft>(Aircraft::Type::Raptor, mTextures);
    rightEscort->setPosition(80.f, 50.f);
    mPlayerAircraft->attachChild(std::move(rightEscort));
}
