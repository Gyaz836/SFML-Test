#ifndef Entity_h__
#define Entity_h__

#include <SFML/System/Vector2.hpp>
#include "SceneNode.h"

class Entity : public SceneNode
{
public:
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);

    sf::Vector2f getVelocity() const;
private:
    sf::Vector2f mVelocity{0, 0};

    void updateCurrent(sf::Time dt) override;

};

#endif // Entity_h__
