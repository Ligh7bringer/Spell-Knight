#include "TextureManager.h"
#include "../../src/Log.h"

std::map<std::string, sf::Texture> TextureManager::_textures;
std::vector<std::string> TextureManager::_resource_directories;

//adds default resource directories
void TextureManager::initialise() {
    addResourceDirectory("res/img/tiles/");
    addResourceDirectory("res/img/");
    addResourceDirectory("res/img/knight/");
}

const sf::Texture& TextureManager::getTexture(const std::string& filename) {
    //check if texture exists
    for(std::map<std::string, sf::Texture>::const_iterator it = _textures.begin(); it != _textures.end(); ++it) {
        if(filename == it->first) {
            //LOG(INFO) << "TextureManager: using existing image for " << filename;
            return it->second;
        }
    }

    //it doesn't exist, load it
    sf::Texture tex;
    if(tex.loadFromFile(filename)) {
        _textures[filename] = tex;
        LOG(INFO) <<  "TextureManager: loading image " << filename;
        return _textures[filename];
    }

    //if it is still not found, search all registered directories
    for(std::vector<std::string>::const_iterator it = _resource_directories.begin(); it != _resource_directories.end(); ++it) {
        if(tex.loadFromFile((*it) + filename)) {
            _textures[filename] = tex;
            LOG(INFO) <<  "TextureManager: texture " << filename << " found in registered resource directory " << *it;
            return _textures[filename];
        }
    }
    
    //texture couldn't be loaded, return empty texture
    LOG(INFO) << "TextureManager: texture " << filename << " couldn't be loaded!";
    _textures[filename] = tex;
    return _textures[filename];
}

//deletes an image from the storage
void TextureManager::deleteImage(const std::string& filename) {
    std::map<std::string, sf::Texture>::const_iterator it = _textures.find(filename);
    if(it != _textures.end()) {
        _textures.erase(it);
    }
}

//adds a resource dir to the list of know dirs
void TextureManager::addResourceDirectory(const std::string& dir) {
    //check if the path already exists
    for(std::vector<std::string>::const_iterator it = _resource_directories.begin(); it != _resource_directories.end(); ++it) {
        //the path exists, no need to add it again
        if(dir == (*it)) {
            LOG(INFO) << "TextureManager: the resource directory " << dir << " already exists...";
            return;
        }
    }

    //it doesn't exist, add it
    _resource_directories.push_back(dir);
    LOG(INFO) << "TextureManager: registering resource directory " << dir;
}

//removes a previously added res dir
void TextureManager::removeResourceDirectory(const std::string& dir) {
     for(std::vector<std::string>::const_iterator it = _resource_directories.begin(); it != _resource_directories.end(); ++it) {
        if(dir == (*it)) {
            it = _resource_directories.erase(it);
            LOG(INFO) << "TextureManager: deleting resource directory " << dir;
        } else if(it != _resource_directories.end()) {
            ++it;
        }
     }
}