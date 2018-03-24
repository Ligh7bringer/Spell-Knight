#pragma once
#include <list>
#include "button.h"

class Menu {
public:
    Menu();

    enum MenuResult { NOTHING, PLAY, OPTIONS, EXIT };

    struct MenuItem {
        Button button;
        MenuResult action;
    };

    void update(double dt);
    void render();

    MenuResult getMenuResponse();

private:
    std::list<MenuItem> _menuItems;
};