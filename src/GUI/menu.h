#pragma once
#include <list>
#include "option_button.h"

class Menu {
public:
    Menu();
    ~Menu() = default;

    void update(double dt);
    void render();

    int getMenuResponse() const;
    void addTitle(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &title);
    void addButton(const sf::Vector2f &pos, const sf::Vector2f& size, const std::string& text);
    void addOptionButton(const sf::Vector2f &pos, const sf::Vector2f& size, const std::vector<std::string>& options);
    void addLabel(unsigned int itemId, const std::string &text);
private:
    unsigned int _id;
    Panel _title;

    //storing the buttons as pointers allows both regular and option buttons to be stored in the same container
    //as option buttons inherit from regular buttons
    std::map<unsigned int, std::shared_ptr<Button>> _buttons;
};