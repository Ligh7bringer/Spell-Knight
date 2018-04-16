#ifndef GAMES_ENGINEERING_AUDIO_MANAGER_H
#define GAMES_ENGINEERING_AUDIO_MANAGER_H

#include <string>
#include <memory>
#include <map>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Sound.hpp>

class AudioManager {
private:
    const static std::string _res_dir;
    static std::map<std::string, std::shared_ptr<sf::Music>> _music;
    static std::map<std::string, std::shared_ptr<sf::SoundBuffer>> _buffers;
    static std::map<std::string, std::shared_ptr<sf::Sound>> _sounds;
    static bool _sound;

public:
    static void initialise();

    static void loadMusic(const std::string& name);
    static void playMusic(const std::string& name, bool loop);
    static void stopMusic(const std::string& name);

    //----------------------------------------------------------
    static void loadSound(const std::string& name);
    static std::shared_ptr<sf::SoundBuffer> getBuffer(const std::string& name);
    static void playSound(const std::string& name);
    static void stopSound(const std::string& name);
    //----------------------------------------------------------
    static void toggleSoundOnOff();

    static bool isSoundOn();
};


#endif //GAMES_ENGINEERING_AUDIO_MANAGER_H
