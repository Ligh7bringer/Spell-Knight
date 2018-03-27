#pragma once
#include "../components/cmp_state_machine.h"
#include <SFML/System/Vector2.hpp>
class SleepingbirdState : public State {
private:
    sf::Vector2f _direction;
public:
    SleepingbirdState() { _direction = sf::Vector2f(1.f, 0); }
    void execute(Entity*, double) noexcept override;
};

class FlyingbirdState : public State {
private:
    bool _setup = true;
    sf::Vector2f _direction;
    std::shared_ptr<Entity> _player;

public:
//    FlyingState();
    explicit FlyingbirdState(std::shared_ptr<Entity>& player) : _player(player), _direction(sf::Vector2f(1.f, 0)) {}
    void execute(Entity*, double) noexcept override;
};