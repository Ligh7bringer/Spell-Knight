#include "cmp_pickup.h"
#include "cmp_player_attack.h"

#ifndef GAMES_ENGINEERING_CMP_POWER_UP_H
#define GAMES_ENGINEERING_CMP_POWER_UP_H


class PowerUpComponent : public PickUpComponent {
private:
    PlayerAttackComponent::AttackType _attackType;

public:
    PowerUpComponent() = delete;
    explicit PowerUpComponent(Entity* p, unsigned int points, PlayerAttackComponent::AttackType type);

    void update(double dt) override;

    void render() override {}

};


#endif //GAMES_ENGINEERING_CMP_POWER_UP_H
