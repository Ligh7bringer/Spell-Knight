#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class InputManager {
public: 
    enum InputType {
        KeyboardInput,
        MouseInput,
        JoystickInput
    };

    struct Key {
        InputType _inputType;
        sf::Event::EventType _eventType;
        sf::Keyboard::Key _keyCode;
        sf::Mouse::Button _mouseButton;
    };

    InputManager() = delete;

    static void initialise();
    static void addKey(const std::string& action, sf::Event::EventType eventType, sf::Keyboard::Key key);
    static sf::Keyboard::Key getKey(const std::string& action);
    static bool isKeyPressed(const std::string& action);

protected:
    static std::map<std::string, Key> _bindings;
};