#pragma once
#include "../../engine/lib_ecm/ecm.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
//#include <SFML/Font.hpp>

class PlayerLivesComponent : public Component {
private:
    int _maxLives;
    int _lives;
    sf::RectangleShape _panel;
    sf::Text _text;
    std::shared_ptr<sf::Font> _font;
    
public:
    PlayerLivesComponent() = delete;
    explicit PlayerLivesComponent(Entity* p, int maxLives);

    void update(double dt) override;
    void render() override;

    void increaseLives(int num);
    void decreaseLives(int num);
    int getLives() const;
};