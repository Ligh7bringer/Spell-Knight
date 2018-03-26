#pragma once
#include "../components/cmp_state_machine.h"
#include <SFML/System/Vector2.hpp>

class RoamingState : public State {
private:
    sf::Vector2f _direction;
public:
    RoamingState() { _direction = sf::Vector2f(1.f, 0); }
    void execute(Entity*, double) noexcept override;
};

class SteeringState : public State {
private:
    sf::Vector2f _direction;
    std::shared_ptr<Entity> _player;
public:
    explicit SteeringState(std::shared_ptr<Entity>& player) : _player(player), _direction(sf::Vector2f(1.f, 0)) {}
    void execute(Entity*, double) noexcept override ;
};

