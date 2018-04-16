#include <settings_parser.h>
#include <SFML/Window/Keyboard.hpp>
#include "config.h"

/*
 * Wrapper class for storing and retrieving settings and strings and some global variables are stored here instead of using externs.
 */

const std::string Config::DEFAULT_SETTINGS_DIR  = "";
const std::string Config::DEFAULT_LANG_DIR = "res/lang/";
const std::string Config::DEFAULT_LANGUAGE = "en.txt";
const std::string Config::SETTINGS_FILE = "settings.txt";
const std::string Config::DEFAULT_FONT = "AMERIKA.ttf";
std::string Config::_currentLanguage = DEFAULT_LANGUAGE;

const std::string &Config::getDefaultSettingsDir() {
    return DEFAULT_SETTINGS_DIR;
}

const std::string &Config::getDefaultLang() {
    return DEFAULT_LANGUAGE;
}

const std::string &Config::getSettingsFile() {
    return SETTINGS_FILE;
}

const std::string &Config::getCurrentLanguage() {
    return _currentLanguage;
}

//returning a copy rather than a reference because returning reference to a temporary string is not good!
const std::string Config::getLocalisedString(const std::string &setting) {
    SettingsParser setPar;
    setPar.readFile(DEFAULT_LANG_DIR + _currentLanguage);
    auto result = setPar.get(setting);
    return result;
}

const std::string Config::getSetting(const std::string &setting) {
    SettingsParser setPar;
    setPar.readFile(DEFAULT_SETTINGS_DIR + SETTINGS_FILE);
    auto result = setPar.get(setting);
    return result;
}

void Config::setSetting(const std::string &key, const std::string &value) {
    SettingsParser setPar;
    setPar.readFile(DEFAULT_SETTINGS_DIR + SETTINGS_FILE);
    setPar.set(key, value);
}

void Config::setCurrentLanguage(const std::string &lang) {
    _currentLanguage = lang;
    SettingsParser sp;
    sp.readFile(DEFAULT_SETTINGS_DIR + SETTINGS_FILE);
    sp.set("language", lang);
}

const std::string &Config::getDefaultFont() {
    return DEFAULT_FONT;
}

//create the settings file if this is the first time the game is run!!!
bool Config::firstRun() {
    SettingsParser sp;
    sp.readFile(DEFAULT_SETTINGS_DIR + SETTINGS_FILE);
    if(sp.get("width").empty()) {
        sp.put("width", "1280");
        sp.put("height", "720");
        sp.put("fullscreen", "0");
        sp.put("language", "en.txt");
        sp.put("walkLeft", std::to_string(sf::Keyboard::A));
        sp.put("walkRight", std::to_string(sf::Keyboard::D));
        sp.put("jump", std::to_string(sf::Keyboard::W));
        sp.put("shoot", std::to_string(sf::Keyboard::Space));
        sp.put("sound", "1");
        sp.saveToFile(false);
        return true;
    }

    return false;
}






