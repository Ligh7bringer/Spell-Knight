#include "../../engine/lib_ecm/ecm.h"
#include <SFML/Graphics/Texture.hpp>

class PlayerBulletComponent : public Component {
private: 
    float _cooldown;
    sf::Texture _spritesheet;
    sf::Vector2f _posOffset;
    float _speed;
    std::vector<std::shared_ptr<Entity>> _bullets;

public:
    void update(double dt) override;
    void render() override;

    void fire();
    std::vector<std::shared_ptr<Entity>> getBullets() const;
    void removeBullet(std::shared_ptr<Entity> b);

    explicit PlayerBulletComponent(Entity* p);
    PlayerBulletComponent() = delete;
};
