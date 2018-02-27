#pragma once
#include "cmp_enemy_animated_sprite.h"
#include "cmp_animated_sprite.h"
#include <SFML/Graphics/Texture.hpp>

class EnemyAnimatedSpriteComponent : public AnimatedSpriteComponent {
protected:
    sf::Texture _enemySpritesheet;

public:
    EnemyAnimatedSpriteComponent() = delete;
    explicit EnemyAnimatedSpriteComponent(Entity* p, int width, int height);

    void update(double dt) override;
    void render() override;
};