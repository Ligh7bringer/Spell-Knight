#include "../../engine/lib_ecm/ecm.h"
#include <SFML/Graphics/Texture.hpp>

class PlayerBulletComponent : public Component {
private: 
    float _cooldown;
    sf::Texture _spritesheet;
    sf::Vector2f _posOffset;
    float _speed;

public:
    void update(double dt) override;
    void render() override;

    void fire();

    explicit PlayerBulletComponent(Entity* p);
    PlayerBulletComponent() = delete;
};
