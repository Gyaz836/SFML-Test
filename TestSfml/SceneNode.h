#ifndef SceneNode_h__
#define SceneNode_h__

#include <memory>
#include <vector>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include "Command.h"

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    using Ptr = std::unique_ptr<SceneNode>;

    SceneNode();
    void attachChild(Ptr child);
    Ptr detachChild(const SceneNode& node);

    sf::Transform getWorldTransform() const;
    sf::Vector2f getWorldPosition() const;

    virtual Category::Type getCategory() const;

    void onCommand(const Command& command, sf::Time dt);

    void update(sf::Time dt);
private:
    virtual void updateCurrent(sf::Time dt);
    virtual void updateChildren(sf::Time dt);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<Ptr> mChildren;
    SceneNode* mParent = nullptr;
};

#endif // SceneNode_h__

