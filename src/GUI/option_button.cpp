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
    for(const auto &option : options) {
        addOption(option);
    }

    _panel.setTextLocalised(_options[_currentOption]);
}

const std::string& OptionButton::getSelection() const {
    return _options[_currentOption];
}

void OptionButton::setSelection(const std::string &sel) {
    auto index = -1;
    for(int i = 0; i < _options.size(); ++i) {
        if(_options[i] == sel) {
            index = i;
            break;
        }
    }

    if(index != -1) {
        _panel.setTextLocalised(_options[index]);
    }
}
