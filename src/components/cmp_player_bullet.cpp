#include "cmp_player_bullet.h"
#include "cmp_bullet.h"
#include "cmp_physics.h"
#include "cmp_animated_sprite.h"
#include "engine.h"
#include <SFML/Graphics/Texture.hpp>
#include "../../engine/lib_texture_manager/TextureManager.h"
#include "cmp_player_physics.h"

using namespace sf;

/*
* This component allows the player to shoot.
*/

//set spritesheet, position of bullet relative to player, speed of bullet
PlayerBulletComponent::PlayerBulletComponent(Entity* p) : Component(p), _cooldown(1.f) {
    _spritesheet = TextureManager::getTexture("WIZARD.png");
    //this offset is needed because the bullet shouldn't be spawned on top of the player, but next to them
    _posOffset = Vector2f(35.f, 5.f);
    _speed = 10.f;
    _cooldown = 0;
}

//don't need to render anything (at the moment)
void PlayerBulletComponent::render() {}

//creates a bullet
void PlayerBulletComponent::fire() {
    //make sure the player hasn't shot in the last 1 second
    if(_cooldown <= 0.0f) {
        //find out which way the player is facing
        auto right = _parent->get_components<AnimatedSpriteComponent>()[0]->isFacingRight();
        //auto right = true;
        auto offset = _posOffset;

        //invert the offset if the player is facing left
        if(!right)
            offset.x = -offset.x;

        //create bullet, set its position to the left/right of the player and add a bullet component
        auto bullet = _parent->scene->makeEntity();
        bullet->setPosition(_parent->getPosition() + offset);
        bullet->addComponent<BulletComponent>();
          
        auto sprite = bullet->addComponent<AnimatedSpriteComponent>(Vector2f(32.f, 32.f));
        sprite->setCurrentRow(4);
        sprite->setSpritesheet(TextureManager::getTexture("projectiles2.png"));
        sprite->setNumberOfFrames(6);
        sprite->setFrameTime(0.15f);

        //add a physics component
        auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(32.f, 20.f));
        //the bullet shouldn't be affected by gravity 
        p->setGravityScale(0.0f);
        p->setRestitution(.4f);
        p->setFriction(.005f);
        //set the appropirate direction
        p->setLinearVelocity(right ? Vector2f(_speed, 0) : Vector2f(-_speed, 0));
        
        _cooldown = 1.f;
    }    
}

void PlayerBulletComponent::update(double dt) {
    //update cooldown
    _cooldown -= dt;
}


