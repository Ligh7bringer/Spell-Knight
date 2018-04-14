#include "menu.h"
#include "../../engine/lib_settings_parser/settings_parser.h"
#include "../game.h"
#include "../Log.h"
#include "option_button.h"

using namespace sf;

//set up the menu items
//TO DO: make this take total size of menu as parameter and calculate button positions rather than using magic numbers
Menu::Menu() : _id(0), _title(Panel(Vector2f(0, 0), Vector2f(0, 0), "Anonymous.ttf")), _btnOffset(Vector2f(0, 50.f)),
                                                                                       _btnSize(Vector2f(200.f, 35.f)),
                                                                                       _position(Vector2f(0, 0)) {}

//returns the id of the button which has been clicked
//returns -1 if no button has been clicked
int Menu::getMenuResponse() const {
    for (const auto &_button : _buttons) {
        if(_button.second->isClicked()) {
            return _button.first;
        }
    }

    return -1;
}

//update buttons
void Menu::update(double dt) {
    _title.update(dt);

    for (auto &_button : _buttons) {
        _button.second->update(dt);
    }
}

//render buttons
void Menu::render() {
    _title.render();

    for (auto &_button : _buttons) {
        _button.second->render();
    }
}

//adds a button to the menu
void Menu::addButton(const std::string &text) {
    auto btn = std::make_shared<Button>(_position + _btnOffset * static_cast<float>(_id), _btnSize, text);
    _buttons[_id] = btn;
    _id++;
}

//adds an option button to the menu
void Menu::addOptionButton(const std::vector<std::string> &options) {
    auto btn = std::make_shared<OptionButton>(_position + _btnOffset * static_cast<float>(_id), _btnSize, "");
    btn->addOptions(options);
    _buttons[_id] = btn;
    _id++;
}

//adds a title for the menu
void Menu::addTitle(const std::string &title) {
    _title = Panel(_position - Vector2f(0, _btnSize.y * 2), _btnSize, "Anonymous.ttf");
    _title.setGUI(false);
    _title.setPanelColour(Color::Transparent);
    _title.setTextLocalised(title);
    _title.setTextColour(Color::White);
}

//adds a label for button with id itemId
void Menu::addLabel(unsigned int itemId, const std::string &text){
    for (auto &_button : _buttons) {
        if(_button.first == itemId) {
            _button.second->addLabel(text);
        }
    }
}

//returns the selected option for button with the given id
const std::string &Menu::getSelectedOption(unsigned int id) const {
    for (auto _button : _buttons) {
        if(_button.first == id) {
            return _button.second->getSelection();
        }
    }

    static const std::string ret = std::string();
    return ret;
}

void Menu::setPosition(const sf::Vector2f &pos) {
    _position = pos;
}

void Menu::setOffset(const sf::Vector2f &offset) {
    _btnOffset = offset;
}



