#ifndef ResourceHolder_h__
#define ResourceHolder_h__

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <cassert>

#include <SFML/Graphics/Texture.hpp>

namespace Textures {
    enum class ID {
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
        std::unique_ptr<Resource> texture = std::make_unique<Resource>();
        if (!texture->loadFromFile(filename))
            throw std::runtime_error("Error in loading texture Id = \"" + std::to_string(static_cast<int>(id)) + "\"");

        auto inserted = mTextureMap.emplace(id, std::move(texture));
        assert(inserted.second);
    }

    template<typename Parameter>
    void load(ID id, const std::string& filename, const Parameter& secondParam)
    {
        std::unique_ptr<Resource> texture = std::make_unique<Resource>();
        if (!texture->loadFromFile(filename, secondParam))
            throw std::runtime_error("Error in loading texture Id = \"" + std::to_string(static_cast<int>(id)) + "\"");

        auto inserted = mTextureMap.emplace(id, std::move(texture));
        assert(inserted.second);
    }

    Resource& get(ID id)
    {
        auto textureIt = mTextureMap.find(id);
        assert(textureIt != mTextureMap.end());
        return *textureIt->second;
    }

    const Resource& get(ID id) const
    {
        auto textureIt = mTextureMap.find(id);
        assert(textureIt != mTextureMap.end());
        return *textureIt->second;
    }

private:
    std::map<ID, std::unique_ptr<sf::Texture>> mTextureMap;
};

using TextureHolder = ResourceHolder<Textures::ID, sf::Texture>;

#endif // ResourceHolder_h__
