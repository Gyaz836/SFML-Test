#include "SceneNode.h"
#include <cassert>

SceneNode::SceneNode() = default;

void SceneNode::attachChild(Ptr child)
{
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
    auto nodeIt = std::find_if(mChildren.begin(), mChildren.end(),
        [&node](Ptr& p) { return &node == p.get(); });
    assert(nodeIt != mChildren.end());
    auto result = std::move(*nodeIt);
    result->mParent = nullptr;
    mChildren.erase(nodeIt);
    return result;
}

sf::Transform SceneNode::getWorldTransform() const
{
    auto ret = getTransform();
    if (mParent != nullptr)
        ret *= mParent->getWorldTransform();
    return ret;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

void SceneNode::update(sf::Time dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time dt)
{

}

void SceneNode::updateChildren(sf::Time dt)
{
    for (auto& child : mChildren) {
        child->update(dt);
    }
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    drawCurrent(target, states);
    drawChildren(target, std::move(states));
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& child : mChildren) {
        child->draw(target, states);
    }
}
