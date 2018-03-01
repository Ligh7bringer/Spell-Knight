#include "TextureManager.h"
#include <iostream>

std::map<std::string, sf::Texture> TextureManager::_textures;
std::vector<std::string> TextureManager::_resource_directories;

const sf::Texture& TextureManager::getTexture(const std::string& filename) {
    //check if texture exists
    for(std::map<std::string, sf::Texture>::const_iterator it = _textures.begin(); it != _textures.end(); ++it) {
        if(filename == it->first) {
            std::cout << "TextureManager: using existing image for " << filename << std::endl;
            return it->second;
        }
    }

    //it doesn't exist, load it
    sf::Texture tex;
    if(tex.loadFromFile(filename)) {
        _textures[filename] = tex;
        std::cout << "TextureManager: loading image " << filename << std::endl;
        return _textures[filename];
    }

    //if it is still not found, search all registered directories
    for(std::vector<std::string>::const_iterator it = _resource_directories.begin(); it != _resource_directories.end(); ++it) {
        if(tex.loadFromFile((*it) + filename)) {
            _textures[filename] = tex;
            std::cout << "TextureManager: texture " << filename << " found in registered resource directory " << *it << std::endl;
            return _textures[filename];
        }
    }
    
    //texture couldn't be loaded, return empty texture
    std::cout << "TextureManager: texture " << filename << " couldn't be loaded!" << std::endl;
    _textures[filename] = tex;
    return _textures[filename];
}

void TextureManager::deleteImage(const std::string& filename) {
    std::map<std::string, sf::Texture>::const_iterator it = _textures.find(filename);
    if(it != _textures.end()) {
        _textures.erase(it);
    }
}

void TextureManager::addResourceDirectory(const std::string& dir) {
    //check if the path already exists
    for(std::vector<std::string>::const_iterator it = _resource_directories.begin(); it != _resource_directories.end(); ++it) {
        //the path exists, no need to add it again
        if(dir == (*it)) {
            std::cout << "TextureManager: the resource directory " << dir << " already exists..." << std::endl;
            return;
        }
    }

    //it doesn't exist, add it
    _resource_directories.push_back(dir);
}

void TextureManager::removeResourceDirectory(const std::string& dir) {
     for(std::vector<std::string>::const_iterator it = _resource_directories.begin(); it != _resource_directories.end(); ++it) {
        if(dir == (*it)) {
            it = _resource_directories.erase(it);
            std::cout << "TextureManager: deleting resource directory " << dir << std::endl;
        } else {
            ++it;
        }
     }
}