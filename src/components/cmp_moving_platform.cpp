#include "cmp_moving_platform.h"
#include "cmp_physics.h"
#include "../../engine/src/system_physics.h"
#include "../Log.h"

using namespace sf;

/*
* This component allows platforms to move back and forth for a specific distance over specific time.
*/

MovingPlatformComponent::MovingPlatformComponent(Entity* p, const Vector2f& dist, float time) : ActorMovementComponent(p), 
                                                _direction(Vector2f(1.f, -1.f)), _velocity(Vector2f(0, 0)),
                                                _distance(dist), _time(time), _dirTimer(time), 
                                                _player(_parent->scene->ents.find("player")[0]),
                                                _physics_scale(Physics::getPhysicsScale()) {}

void MovingPlatformComponent::update(double dt) {
    auto physics = _parent->GetCompatibleComponent<PhysicsComponent>()[0];
    //update timer
    _dirTimer -= dt;
    
    //if time is up
    if(_dirTimer <= 0) {
        //reset timer
        _dirTimer = _time;
        //reverse direction
        _direction.x *= -1.f;
        _direction.y *= -1.f;
    }
    
    //calculate velocity
    _velocity.x = _distance.x * (1.f/_physics_scale) / _time;
    _velocity.y = _distance.y * (1.f/_physics_scale) / _time;

    //set velocity
    physics->setLinearVelocity(_velocity * _direction);

    if(auto player = _player.lock()) {
        auto playerPhysics = player->GetCompatibleComponent<PhysicsComponent>()[0];
        //if the player is touching the platform
        if(physics->isTouching(*playerPhysics)) {
            //calculate velocity
            auto targetVel = playerPhysics->getMass() * (physics->getVelocity() - playerPhysics->getVelocity()) / _physics_scale;
            //ignore y velocity
            targetVel.y = 0;
            //impulse
            playerPhysics->impulse(targetVel);
        }
    }
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

