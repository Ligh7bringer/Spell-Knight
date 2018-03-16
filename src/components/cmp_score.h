#pragma once
#include "../../engine/lib_ecm/ecm.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

class PlayerScoreComponent : public Component {
protected:
    sf::RectangleShape _panel;
    sf::Text _text;
    std::shared_ptr<sf::Font> _font;
    int _points;

public:
    PlayerScoreComponent() = delete;
    explicit PlayerScoreComponent(Entity* p);

    void update(double dt) override;
    void render() override;

    void increasePoints(int num);
    void decreasePoints(int num);
    int getPoints() const;
};