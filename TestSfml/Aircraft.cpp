#include "Aircraft.h"
#include <SFML/Graphics/RenderTarget.hpp>

Textures::ID Aircraft::typeToTextureType(Type type)
{
    switch (type)
    {
    case Aircraft::Type::Eagle:
        return Textures::ID::Eagle;
    case Aircraft::Type::Raptor:
        return Textures::ID::Raptor;
    }
    throw std::logic_error("Unknown type");
}

Category::Type Aircraft::getCategory() const
{
    return Category::Type::AnyAircraft;
}

Aircraft::Aircraft(Type type, const TextureHolder& holder)
    : mType(type)
    , mSprite(holder.get(typeToTextureType(type)))
{
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2, bounds.height / 2);
}

void Aircraft::accelerate(sf::Vector2f velocity)
{
    setVelocity(getVelocity() + velocity);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
