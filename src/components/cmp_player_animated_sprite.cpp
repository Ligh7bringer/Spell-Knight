#include "cmp_player_animated_sprite.h"
#include "cmp_player_physics.h"
#include <SFML/Graphics.hpp>
#include "../../engine/lib_texture_manager/TextureManager.h"

using namespace std;
using namespace sf;

PlayerAnimatedSpriteComponent::PlayerAnimatedSpriteComponent(Entity *p, int width, int height) : AnimatedSpriteComponent(p, width, height) {
    //load spritesheet 
    _knightSpritesheet = TextureManager::getTexture("WIZARD.png");

    //set spritesheet
    setSpritesheet(_knightSpritesheet);
    setNumberOfFrames(4);
    //set padding
    setSpriteSheetPadding(2);   
    setFrameTime(0.15f);
    _lastDir = 1;
    _hurt = false;
    _hurtTimer = 1.f;
}

void PlayerAnimatedSpriteComponent::update(double dt) {
    if(_hurt) {
        _hurtTimer -= dt;
        static int alpha = 127;
        alpha -= 5;
        _sprite.setColor(Color(255, 255, 255, alpha));
    }

    if(_hurt && _hurtTimer <= 0.f) {
        _hurt = false;
        _hurtTimer = 1.0f;
        _sprite.setColor(Color(255, 255, 255, 255));
    }

    //get the physics component, this could be put outside of update possibly?
    auto physicsComp = _parent->get_components<PlayerPhysicsComponent>()[0];
    //get direction and whether the player is jumping
    auto dir = physicsComp->getDirection();
    auto jumping = physicsComp->isJumping();

    //decide which animation to play based on the values above
    if(jumping) {
        setCurrentRow(2);
        setFacingRight(dir == 1);
        //_lastDir = dir;
    } else if(dir == 1) {
        setCurrentRow(1);
        setFacingRight(true);
       _lastDir = dir; //lastDir is used to determine which idle animation should be played when the player stops moving
    } else if(dir == -1) {
        setCurrentRow(1);
        setFacingRight(false);
        _lastDir = dir;    
    } else {
        setCurrentRow(0);
        setFacingRight(_lastDir == 1);
    } 

    if(physicsComp->isShooting()) {
        setCurrentRow(3);
        //setFacingRight(false);
    }

    //call super's update which will take care of everything else
    AnimatedSpriteComponent::update(dt);
}

//just use super's render
void PlayerAnimatedSpriteComponent::render() {
    AnimatedSpriteComponent::render();    
}

void PlayerAnimatedSpriteComponent::setHurt(bool h) {
    _hurt = h;
}

bool PlayerAnimatedSpriteComponent::isHurt() {
    return _hurt;
}