#pragma once
#include "cmp_actor_movement.h"
#include <ecm.h>

class MovingPlatformComponent : public ActorMovementComponent {
private:
    sf::Vector2f _velocity;
    sf::Vector2f _direction;
    sf::Vector2f _distance;
    float _time;
    float _dirTimer;

public:
    MovingPlatformComponent() = delete;
    explicit MovingPlatformComponent(Entity* p, const sf::Vector2f& dist, float time);

    void update(double dt) override;
    void render() override;

    void setTravelDistance(const sf::Vector2f& dist);
    void setTime(float t);
};