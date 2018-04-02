#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <map>


class TextureManager {
public:
    static void initialise();
    static const sf::Texture& getTexture(const std::string& filename);
    static void deleteImage(const std::string& filename);
    static void deleteImage(const sf::Texture* texture);
    static void addResourceDirectory(const std::string& dir);
    static void removeResourceDirectory(const std::string& dir);

private:
    static std::map<std::string, sf::Texture> _textures;     
    static std::vector< std::string > _resource_directories;
};