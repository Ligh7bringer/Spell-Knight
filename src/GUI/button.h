#pragma once

#include "panel.h"
#include <memory>

class Button {
protected:
    sf::RectangleShape _shape;
    sf::Vector2f _position;
    sf::Vector2f _size;
    sf::Text _text;
    std::shared_ptr<sf::Font> _font;
    bool _clicked;

    Panel _panel;

    sf::FloatRect getMouseRect(int width, int height);
    void onClick();
    void onHover();
    void reset();

public:
    explicit Button(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& text);
    Button() = default;

    void update(double dt);
    void render();

    void setPosition(const sf::Vector2f& pos);
    bool isClicked() const;
};
