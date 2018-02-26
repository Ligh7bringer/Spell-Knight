#include "cmp_player_animated_sprite.h"
#include "cmp_player_physics.h"

using namespace std;
using namespace sf;

PlayerAnimatedSpriteComponent::PlayerAnimatedSpriteComponent(Entity *p) : AnimatedSpriteComponent(p, 64, 64) {
    //load spritesheet 
    if(!_knightSpritesheet.loadFromFile("res/img/knight/spritesheet _knight.png")) {
        cout << "Couldnt load knight sprite sheet!" << endl;
    }

    //set spritesheet
    setSpritesheet(_knightSpritesheet);
    //set padding
    setSpriteSheetPadding(1);   
    _lastDir = 1;
}

void PlayerAnimatedSpriteComponent::update(double dt) {
    //get the physics component, this could be put outside of update possibly?
    auto physicsComp = _parent->get_components<PlayerPhysicsComponent>()[0];
    //get direction and whether the player is jumping
    auto dir = physicsComp->getDirection();
    auto jumping = physicsComp->isJumping();

    //decide which animation to play based on the values above
    if(jumping) {
        setCurrentRow(1);
        setNumberOfFrames(5);
        setFacingRight(dir == 1);
        //_lastDir = dir;
    } else if(dir == 1) {
        setCurrentRow(2);
        setNumberOfFrames(3);
        setFacingRight(true);
       _lastDir = dir; //lastDir is used to determine which idle animation should be played when the player stops moving
    } else if(dir == -1) {
        setCurrentRow(2);
        setNumberOfFrames(3);
        setFacingRight(false);
        _lastDir = dir;    
    } else {
        setCurrentRow(0);
        setNumberOfFrames(8);
        setFacingRight(_lastDir == 1 ? true : false);
    } 

    //_lastDir = dir;

    //call super's update which will take care of everything else
    AnimatedSpriteComponent::update(dt);
}

//just use super's render
void PlayerAnimatedSpriteComponent::render() {
    AnimatedSpriteComponent::render();    
}