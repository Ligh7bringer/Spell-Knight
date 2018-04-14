#pragma once

#include "panel.h"
#include <memory>

class Button {
protected:
    bool _clicked;
    Panel _panel;
    bool _check;
    float _timer;
    sf::Vector2f _position;
    Panel _label;

    sf::FloatRect getMouseRect(unsigned int width, unsigned int height);
    virtual void onClick();
    virtual void onHover();
    virtual void reset();

public:
    explicit Button(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& text);
    Button() = default;

    void update(double dt);
    void render();

    void setPosition(const sf::Vector2f& pos);
    const sf::Vector2f& getPosition();
    bool isClicked() const;

    void addLabel(const std::string& text);

    virtual const std::string& getSelection() const;
};
