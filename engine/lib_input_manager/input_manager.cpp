#include "input_manager.h"
#include "../../src/Log.h"
#include "../../src/config.h"

using namespace sf;
using namespace std;

/*
* This class allows storing, retrieving and changing key bindings for specific (player) actions.
*/

//map where key bindings are stored as a string which describes the action (e.g. shoot, jump) and a Key object which
//contains the event type, input type, etc.
std::map<std::string, InputManager::Key> InputManager::_bindings;

//adds default controls
void InputManager::initialise() {
    addKey("jump", Event::KeyPressed, static_cast<sf::Keyboard::Key>(stoi(Config::getSetting("jump"))));
    addKey("shoot", Event::KeyPressed, static_cast<sf::Keyboard::Key>(stoi(Config::getSetting("shoot"))));
    addKey("walkLeft", Event::KeyPressed, static_cast<sf::Keyboard::Key>(stoi(Config::getSetting("walkLeft"))));
    addKey("walkRight", Event::KeyPressed, static_cast<sf::Keyboard::Key>(stoi(Config::getSetting("walkRight"))));
    //LOG(DEBUG) << static_cast<sf::Keyboard::Key>(stoi(Config::getSetting("jump")));
}

//adds a key binding
//assumes you want to add a keyboard key as this is the only input device we are using at the moment
void InputManager::addKey(const string& action, sf::Event::EventType eventType, sf::Keyboard::Key key) {
    Key __key{};

    __key._inputType = KeyboardInput;
    __key._eventType = eventType;
    __key._keyCode = key;
    
    bool overwrite = false;

    //if key exists, overwrite it
    for (auto &_binding : _bindings) {
        if(action == _binding.first) {
            LOG(INFO) << "Overwriting existing key binding for action " + action << " with key " << key << "!";
            _binding.second = __key;
            overwrite = true;
        }
    }

    //if not, add it to the map
    if(!overwrite) {
        _bindings[action] = __key;
        LOG(INFO) << "Adding a key binding for action " << action << " with key " << key;
    }
}

//returns key code for a key
//if the key does not exist in the _bindings map, nothing will be returned
//and the isKeyPressed method will always return false!
sf::Keyboard::Key InputManager::getKey(const string& action) {
    return _bindings[action]._keyCode;
}

bool InputManager::isKeyPressed(const std::string &action) {
    return sf::Keyboard::isKeyPressed(_bindings[action]._keyCode);
}


