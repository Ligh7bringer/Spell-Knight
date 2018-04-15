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
    void addTitle(const std::string &title);
    void addButton(const std::string& text);
    void addOptionButton(const std::vector<std::string>& options);
    void addLabel(unsigned int itemId, const std::string &text);
    const std::string& getSelectedOption(unsigned int id) const;
    void setOffset(const sf::Vector2f& offset);
    void setPosition(const sf::Vector2f& pos);
    void repositionMenu();

private:
    unsigned int _id;
    Panel _title;
    sf::Vector2f _btnOffset;
    sf::Vector2f _btnSize;
    sf::Vector2f _position;
    sf::Vector2f _totalSize;

    //storing the buttons as pointers allows both regular and option buttons to be stored in the same container
    //as option buttons inherit from regular buttons
    std::map<unsigned int, std::shared_ptr<Button>> _buttons;
};