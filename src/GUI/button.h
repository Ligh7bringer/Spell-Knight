#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Button {
protected:
    sf::RectangleShape _shape;
    sf::Vector2f _position;
    sf::Vector2f _size;
    sf::Text _text;
    std::shared_ptr<sf::Font> _font;
    bool _clicked;

    sf::FloatRect getMouseRect(int width, int height);
    sf::FloatRect getBtnRect();
    virtual void onClick();
    virtual void onHover();
    virtual void reset();

public:
    Button(const sf::Vector2f& pos, const std::string& text);
    Button() = default;

    void update(double dt);
    void render();

    void setPosition(const sf::Vector2f& pos);
    bool isClicked() const;

    //sf::RectangleShape& getShape();

};
