#include "cmp_moving_platform.h"
#include "cmp_physics.h"
#include "../Log.h"

using namespace sf;

const float physics_scale = 30.f;
const float physics_scale_inv = 1.0f / physics_scale;


MovingPlatformComponent::MovingPlatformComponent(Entity* p, const Vector2f& dist, float time) : ActorMovementComponent(p), 
                                                _direction(Vector2f(1.f, -1.f)), _velocity(Vector2f(0, 0)),
                                                _distance(dist), _time(time), _dirTimer(time) {}

void MovingPlatformComponent::update(double dt) {
    //LOG(DEBUG) << _distance;
    auto physics = _parent->GetCompatibleComponent<PhysicsComponent>()[0];
    _dirTimer -= dt;
    
    if(_dirTimer <= 0) {
        _dirTimer = _time;
        _direction.x *= -1;
        _direction.y *= -1;
    }

    _velocity.x = _distance.x * physics_scale_inv / _time;
    _velocity.y = _distance.y * physics_scale_inv / _time;

    physics->setLinearVelocity(_velocity * _direction);
}

//sets the distance the platform should travel before reversing direction
void MovingPlatformComponent::setTravelDistance(const Vector2f& dist) {
    _distance = dist;
}

//sets how long it should take the platform to travel its distance
void MovingPlatformComponent::setTime(float t) {
    _time = t;
    _dirTimer = t;
}

//nothing to render
void MovingPlatformComponent::render() {}

