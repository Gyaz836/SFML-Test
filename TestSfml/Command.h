#ifndef Command_h__
#define Command_h__

#include <functional>

#include "SFML/System/Time.hpp"

namespace Category
{
    enum class Type : size_t
    {
        None,
        Scene = 1 << 0,
        PlayerAircrarft = 1 << 1,
        AlliedAircrarft = 1 << 2,
        EnemyAircrarft = 1 << 3,

        AnyAircraft = PlayerAircrarft | AlliedAircrarft | EnemyAircrarft,
    };

    Type operator|(Type lhs, Type rhs);
    Type operator&(Type lhs, Type rhs);
}

class SceneNode;
struct Command
{
    std::function<void(SceneNode&, sf::Time)> action;
    Category::Type category;
};

#endif // Command_h__

