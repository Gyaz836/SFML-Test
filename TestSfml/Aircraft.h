#ifndef Aircraft_h__
#define Aircraft_h__

#include "Entity.h"

#include <SFML/Graphics/Sprite.hpp>

#include "ResourceHolder.h"

class Aircraft : public Entity
{
public:
    using Ptr = std::unique_ptr<Aircraft>;

    enum class Type
    {
        Eagle,
        Raptor
    };
    Textures::ID typeToTextureType(Type type);
public:
    Aircraft(Type type, const TextureHolder& holder);
private:
    Type mType;
    sf::Sprite mSprite;

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif // Aircraft_h__
