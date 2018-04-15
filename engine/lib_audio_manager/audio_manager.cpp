#include "audio_manager.h"
#include "../../src/Log.h"

using namespace sf;

/*
 * Stores and manages sounds and music.
 */

//directory to load sounds from
const std::string AudioManager::_res_dir =  "res/sounds/";

//maps to store music, sounds and buffers
std::map<std::string, std::shared_ptr<sf::Music>> AudioManager::_music;
std::map<std::string, std::shared_ptr<sf::SoundBuffer>> AudioManager::_buffers;
std::map<std::string, std::shared_ptr<sf::Sound>> AudioManager::_sounds;

//loads all necessary sounds and music so they are ready to be used
void AudioManager::initialise() {
    AudioManager::loadMusic("background.wav");
    AudioManager::loadSound("death.wav");
    AudioManager::loadSound("shoot.wav");
    AudioManager::loadSound("explosion.wav");
    AudioManager::loadSound("collect.wav");
    AudioManager::loadSound("teleport.wav");
	  AudioManager::loadSound("fireball.wav");
	  AudioManager::loadSound("shock.wav");
    LOG(INFO) << "Audio manager initialised!";
}

// ---- MUSIC ----
//loads music and puts in the music map
void AudioManager::loadMusic(const std::string &name) {
    auto music = std::make_shared<Music>();
    if(music->openFromFile(_res_dir + name))
        _music[name] = music;
    else
        LOG(ERROR) << "Couldn't open music file " + name;
}

//plays music which has already been loaded
void AudioManager::playMusic(const std::string &name, bool loop) {
    for(std::map<std::string, std::shared_ptr<Music>>::const_iterator it = _music.begin(); it != _music.end(); ++it) {
        if(name == it->first) {
            it->second->setLoop(loop);
            it->second->play();
        }
    }
}

//stops music if it's currently being played
void AudioManager::stopMusic(const std::string &name) {
    for(std::map<std::string, std::shared_ptr<Music>>::const_iterator it = _music.begin(); it != _music.end(); ++it) {
        if(name == it->first) {
            it->second->stop();
        }
    }
}

// ---- SOUNDS ----
//loads a sound file
void AudioManager::loadSound(const std::string &name) {
    //create buffer
    auto buffer = std::make_shared<SoundBuffer>();
    //load sound into it
    if(buffer->loadFromFile(_res_dir + name)) {
        //store buffer
        _buffers[name] = buffer;

        //create sound
        auto sound = std::make_shared<Sound>();
        //set its buffer
        sound->setBuffer(*buffer);
        //and store it
        _sounds[name] = sound;
    } else {
        LOG(ERROR) << "Couldn't load sound file " + name;
    }
}

//plays a sound which has been loaded
void AudioManager::playSound(const std::string &name) {
    for(std::map<std::string, std::shared_ptr<Sound>>::const_iterator it = _sounds.begin(); it != _sounds.end(); ++it) {
        if(name == it->first) {
            it->second->play();
        }
    }
}

//finds and returns a specific buffer
std::shared_ptr<sf::SoundBuffer> AudioManager::getBuffer(const std::string &name) {
    for(std::map<std::string, std::shared_ptr<SoundBuffer>>::const_iterator it = _buffers.begin(); it != _buffers.end(); ++it) {
        if(it->first == name) {
            return it->second;
        }
    }

    return nullptr;
}

//stops a sound if it's currently playing
void AudioManager::stopSound(const std::string &name) {
    for(std::map<std::string, std::shared_ptr<Sound>>::const_iterator it = _sounds.begin(); it != _sounds.end(); ++it) {
        if(it->first == name) {
            return it->second->stop();
        }
    }
}


