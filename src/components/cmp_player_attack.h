#include "../../engine/lib_ecm/ecm.h"
#include <SFML/Graphics/Texture.hpp>

class PlayerAttackComponent : public Component {
public:
    enum AttackType
    {
        DEFAULT,
        FIREBALL,
        ICICLE
    };

    struct Attack {
        AttackType type;
        int damage;
        float cooldown;
        sf::Vector2f spriteSize;
        std::string spriteSheet;
        int frameCount;
        int row;
    };

    void update(double dt) override;
    void render() override;

    void fire();
    void changeAttack(AttackType at);

    explicit PlayerAttackComponent(Entity* p);
    PlayerAttackComponent() = delete;

private: 
    float _cooldown;
    sf::Texture _spritesheet;
    sf::Vector2f _posOffset;
    float _speed;
    Attack _currentAttack;
    std::vector<Attack> _availableAttacks;

    void initAttacks();
};
