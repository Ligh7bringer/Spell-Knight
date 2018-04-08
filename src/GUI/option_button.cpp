#include "option_button.h"

OptionButton::OptionButton(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &text) :
                                                                                Button(pos, size, text),
                                                                                _currentOption(0) {
    //_options.push_back(text);
}

void OptionButton::onClick() {
    _currentOption++;
    if(_currentOption > _options.size() - 1) {
        _currentOption = 0;
    }

    _panel.setTextLocalised(_options[_currentOption]);
    Button::onClick();
}

void OptionButton::addOption(const std::string &option) {
    _options.push_back(option);
}

void OptionButton::addOptions(const std::vector<std::string> &options) {
    for(auto option : options) {
        addOption(option);
    }
}

unsigned int OptionButton::getSelection() {
    return _currentOption;
}
