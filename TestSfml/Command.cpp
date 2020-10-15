#include "Command.h"

namespace Category
{

    Type operator|(Type lhs, Type rhs)
    {
        return static_cast<Type>(static_cast<size_t>(lhs) | static_cast<size_t>(rhs));
    }

    Type operator&(Type lhs, Type rhs)
    {
        return static_cast<Type>(static_cast<size_t>(lhs) & static_cast<size_t>(rhs));
    }
}
