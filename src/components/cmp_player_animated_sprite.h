#pragma once
#include "cmp_animated_sprite.h"
#include <SFML/Graphics/Texture.hpp>

class PlayerAnimatedSpriteComponent : public AnimatedSpriteComponent {
protected:
    sf::Texture _knightSpritesheet;
    int _lastDir; 

public:
    PlayerAnimatedSpriteComponent() = delete;
    explicit PlayerAnimatedSpriteComponent(Entity* p, int width, int height);

    void update(double dt) override;
    void render() override;
};