#include "cmp_power_up.h"

PowerUpComponent::PowerUpComponent(Entity *p, unsigned int points, PlayerAttackComponent::AttackType type) : PickUpComponent(p, points),
                                                                                                              _attackType(type) {}

void PowerUpComponent::update(double dt) {
    if(auto player = _player.lock()) {
        if(sf::length(player->getPosition() - _parent->getPosition()) <= 25.f) {
            auto attackComp = player->get_components<PlayerAttackComponent>()[0];
            attackComp->changeAttack(_attackType);
        }
    }

    PickUpComponent::update(dt);
}
