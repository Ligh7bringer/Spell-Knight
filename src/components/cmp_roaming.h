#pragma once
#include "../../engine/src/engine.h"

class RoamingComponent : public Component {
private:
    sf::Vector2f _velocity;
    sf::Vector2f _direction;
    sf::Vector2f _distance;
    float _time;
    float _dirTimer;
    std::weak_ptr<Entity> _player;
    float _physics_scale;
    bool _isPlatform;

public:
    RoamingComponent() = delete;
    explicit RoamingComponent(Entity* p, const sf::Vector2f& dist, float time, bool platform);

    void update(double dt) override;
    void render() override;

    void setTravelDistance(const sf::Vector2f& dist);
    void setTime(float t);
};