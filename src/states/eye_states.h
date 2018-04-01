#pragma once
#include "../components/cmp_state_machine.h"
#include <SFML/System/Vector2.hpp>

class SleepingState : public State {
private:
    std::shared_ptr<Entity> _player;
    std::string _nextState;

public:
    SleepingState() = delete;
    explicit SleepingState(std::shared_ptr<Entity>& player, const std::string& nextState) : _player(player),
                                                                                            _nextState(nextState) {}

    void execute(Entity*, double) noexcept override;
};

class FlyingState : public State {
private:   
    bool _setup = true;
    sf::Vector2f _direction;

public:
    FlyingState();

    void execute(Entity*, double) noexcept override;
};