#include "eye_states.h"
#include "../components/cmp_animated_sprite.h"
#include "../components/cmp_enemy_physics.h"
#include "../Log.h"
#include "../../engine/lib_texture_manager/TextureManager.h"

/*
* Behaviour of the flying eye creature.
*/

using namespace sf;

// ----- Sleeping state ------
void SleepingState::execute(Entity* owner, double dt) noexcept {
    //if distance to player is less than 300
    if(length(owner->getPosition() - _player->getPosition()) < 300.f) {  
        auto sm = owner->get_components<StateMachineComponent>()[0];
        //go to flying state
        sm->changeState("flying");
    }
}

// ----- Flying state -----
FlyingState::FlyingState() : _direction(Vector2f(1,0)) {}

void FlyingState::execute(Entity* owner, double dt) noexcept {
    //this only needs to happen once
    // if(_setup) {
    //     //change animation
    //     auto anim = owner->get_components<AnimatedSpriteComponent>()[0];
    //     anim->setSpritesheet(TextureManager::getTexture("eyeflying.png"));
    //     anim->setNumberOfFrames(4);

    //     //set the enemy to an air enemy so that it starts fly
    //     auto physics = owner->get_components<EnemyPhysicsComponent>()[0];
    //     physics->setAir(true);

    //     _setup = false;
    // }

    if(_setup) {
        auto anim = owner->get_components<AnimatedSpriteComponent>()[0];
        anim->setSpritesheet(TextureManager::getTexture("eyeflying.png"));
        anim->setNumberOfFrames(4);
        _setup = false;
    }

    auto physics = owner->get_components<EnemyPhysicsComponent>()[0];

    const auto pos = owner->getPosition() ;
     auto mov = _direction * (float)(dt * 100);
     mov.x += _direction.x * 16.f;
	
    //check if the creature is certain height above ground
  if(physics->isGrounded()) {
    physics->setVelocity(Vector2f(physics->getVelocity().x, 0.f));
    physics->teleport(Vector2f(pos.x, pos.y - 1.0f));
    physics->impulse(Vector2f(0, -8.f));

    // Dampen X axis movement
    physics->dampen({0.9f, 1.0f});
    _direction = Vector2f(0, 1);
  }

}