#ifndef ResourceHolder_h__
#define ResourceHolder_h__

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <cassert>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Fonts {
    enum class ID {
        Sansation,
    };
}

namespace Textures {
    enum class ID {
        TitleBackground,

        Desert,

        Missile,

        Eagle,
        Raptor,
    };
}

template<typename ID, typename Resource>
class ResourceHolder
{
public:
    void load(ID id, const std::string& filename)
    {
        std::unique_ptr<Resource> resource = std::make_unique<Resource>();
        if (!resource->loadFromFile(filename))
            throw std::runtime_error("Error in loading resource Id = \"" + std::to_string(static_cast<int>(id)) + "\"");

        auto inserted = mResourceMap.emplace(id, std::move(resource));
        assert(inserted.second);
    }

    template<typename Parameter>
    void load(ID id, const std::string& filename, const Parameter& secondParam)
    {
        std::unique_ptr<Resource> resource = std::make_unique<Resource>();
        if (!resource->loadFromFile(filename, secondParam))
            throw std::runtime_error("Error in loading resource Id = \"" + std::to_string(static_cast<int>(id)) + "\"");

        auto inserted = mResourceMap.emplace(id, std::move(resource));
        assert(inserted.second);
    }

    Resource& get(ID id)
    {
        auto resourceIt = mResourceMap.find(id);
        assert(resourceIt != mResourceMap.end());
        return *resourceIt->second;
    }

    const Resource& get(ID id) const
    {
        auto resourceIt = mResourceMap.find(id);
        assert(resourceIt != mResourceMap.end());
        return *resourceIt->second;
    }

private:
    std::map<ID, std::unique_ptr<Resource>> mResourceMap;
};

using TextureHolder = ResourceHolder<Textures::ID, sf::Texture>;
using FontHolder = ResourceHolder<Fonts::ID, sf::Font>;

#endif // ResourceHolder_h__
