#include "menu.h"
#include "../../engine/lib_settings_parser/settings_parser.h"
#include "../game.h"

using namespace sf;

SettingsParser settings;
SettingsParser language;
//set up the menu items
//TO DO: make this take total size of menu as parameter and calculate button positions rather than using magic numbers
Menu::Menu() : _id(0) {}

//returns which button is clicked 
//returns NOTHING if no button has been clicked
int Menu::getMenuResponse() const {
    for (auto it = _menuItems.begin(); it != _menuItems.end(); ++it) {
        if(it->button.isClicked()) {
            return it->id;
        }
    }

    return -1;
}

//update buttons
void Menu::update(double dt) {
    std::list<MenuItem>::iterator it;
    _title.update(dt);
    _label.update(dt);
    for ( it = _menuItems.begin(); it != _menuItems.end(); ++it) {
        it->button.update(dt);
    }
}

//render buttons
void Menu::render() {
    std::list<MenuItem>::iterator it;

    _title.render();
    _label.render();
    for ( it = _menuItems.begin(); it != _menuItems.end(); ++it) {
        it->button.render();
    }
}

//adds a button to the menu
void Menu::addButton(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &text) {
    MenuItem item;
    item.button = Button(pos, size, text);
    item.id = _id;
    _id++;

    _menuItems.push_back(item);
}

void Menu::addTitle(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &title) {
    _title= Panel(pos, size, "Anonymous.ttf");
    _title.setGUI(false);
    _title.setPanelColour(Color::Transparent);
    _title.setTextLocalised(title);
    _title.setTextColour(Color::White);
}

void Menu::addLabel(unsigned int itemId, const std::string &text){
    for(auto it = _menuItems.begin(); it != _menuItems.end(); ++it) {
      if(it->id == itemId) {
        _label = Panel(Vector2f(it->button.getPosition().x -150, it->button.getPosition().y), Vector2f(100,35), "Anonymous.ttf");
        _label.setGUI(false);
        _label.setPanelColour(Color::Transparent);
        _label.setTextLocalised(text);
        _label.setTextColour(Color::White);
      }
    }
}


