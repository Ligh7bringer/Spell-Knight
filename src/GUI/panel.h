#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <memory>

class Panel {
protected:
    sf::Vector2f _size;
    sf::Vector2f _position;
    std::string _renderString;
    sf::RectangleShape _rect;
    sf::Text _text;
    std::shared_ptr<sf::Font> _font;

    void recentreText();
    void resizePanel();

public:
    Panel() = default;
    Panel(const sf::Vector2f& size, const sf::Vector2f& pos, const std::string& font);

    void update(double dt);
    void render();

    void setText(const std::string& text);

    void setPanelColour(const sf::Color& colour);
    void setTextColour(const sf::Color& colour);
};