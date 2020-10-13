#ifndef SpriteNode_h__
#define SpriteNode_h__

#include "SceneNode.h"
#include <SFML/Graphics/Sprite.hpp>

class SpriteNode : public SceneNode
{
public:
    using Ptr = std::unique_ptr<SpriteNode>;

    SpriteNode(const sf::Texture& texture);
    SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);
private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Sprite mSprite;
};

#endif // SpriteNode_h__
