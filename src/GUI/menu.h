#pragma once
#include <list>
#include "button.h"

class Menu {
public:
    Menu();

    struct MenuItem {
        Button button;
        unsigned int id;
    };

    void update(double dt);
    void render();

    int getMenuResponse() const;
    void addTitle(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &title);
    void addButton(const sf::Vector2f &pos, const sf::Vector2f& size, const std::string& text);
    void addLabel(unsigned int itemId, const std::string &text);
private:
    unsigned int _id;
    Panel _title;
    Panel _label;
    std::list<MenuItem> _menuItems;
};