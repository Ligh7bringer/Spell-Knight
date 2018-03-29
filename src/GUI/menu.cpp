#include "menu.h"
#include "../../engine/lib_settings_parser/settings_parser.h"

using namespace sf;

SettingsParser settings;
//set up the menu items
//TO DO: make this take total size of menu as parameter and calculate button positions rather than using magic numbers
Menu::Menu() {
    settings.readFile("res/lang/en.txt");

    //Play menu item 
    MenuItem playButton;
    playButton.button = Button(Vector2f(500, 350), Vector2f(200, 35), settings.get("play"));
    playButton.action = PLAY;

    //options menu item
    MenuItem optionsButton;
    optionsButton.button = Button(Vector2f(500, 400), Vector2f(200, 35), settings.get("options"));
    optionsButton.action = OPTIONS;

    //exit menu item 
    MenuItem exitButton;
    exitButton.button = Button(Vector2f(500, 450), Vector2f(200, 35), settings.get("exit"));
    exitButton.action = EXIT;

    _menuItems.push_back(playButton);
    _menuItems.push_back(optionsButton);
    _menuItems.push_back(exitButton);
}

//returns which button is clicked 
//returns NOTHING if no button has been clicked
Menu::MenuResult Menu::getMenuResponse() {
    std::list<MenuItem>::iterator it;

    for ( it = _menuItems.begin(); it != _menuItems.end(); ++it) {
        if(it->button.isClicked()) {
            return it->action;
        }
    }

    return NOTHING;
}

//update buttons
void Menu::update(double dt) {
    std::list<MenuItem>::iterator it;

    for ( it = _menuItems.begin(); it != _menuItems.end(); ++it) {
        it->button.update(dt);
    }
}

//render buttons
void Menu::render() {
    std::list<MenuItem>::iterator it;

    for ( it = _menuItems.begin(); it != _menuItems.end(); ++it) {
        it->button.render();
    }
}
