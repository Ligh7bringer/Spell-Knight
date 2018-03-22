#include "eye_states.h"
#include "../components/cmp_animated_sprite.h"
#include "../components/cmp_enemy_physics.h"
#include "../Log.h"
#include "../../engine/lib_texture_manager/TextureManager.h"

/*
* Behaviour of the flying eye creature.
*/

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
void FlyingState::execute(Entity* owner, double dt) noexcept {
    //this only needs to happen once
    if(_setup) {
        //change animation
        auto anim = owner->get_components<AnimatedSpriteComponent>()[0];
        anim->setSpritesheet(TextureManager::getTexture("eyeflying.png"));
        anim->setNumberOfFrames(4);

        //set the enemy to an air enemy so that it starts fly
        auto physics = owner->get_components<EnemyPhysicsComponent>()[0];
        physics->setAir(true);

        _setup = false;
    }
}