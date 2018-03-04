#include "cmp_bullet.h"
#include "cmp_player_bullet.h"
#include "cmp_physics.h"
#include "cmp_animated_sprite.h"
#include "cmp_enemy_physics.h"
#include "../../engine/lib_texture_manager/TextureManager.h"
#include "system_physics.h"
#include "../../engine/src/engine.h"
#include "../../engine/lib_ecm/ecm.h"
#include <iostream>

using namespace std;
using namespace sf;

void BulletComponent::update(double dt) {
  //get the collisions from the physics component
  auto contacts = _parent->get_components<PhysicsComponent>()[0]->getTouching();

  _lifetime -= dt;
  //timer to set a delay so the whole explosion animation can be played before the bullet is destroyed
  _explosionTime -= dt;
  
  //if its touching anything or its lifetime counter has reached 0
  if ((_lifetime <= 0.f || contacts.size() > 0) && !_exploded) { 
    checkCollisions(contacts);
    explode();
  } 
  
  //if the "timer" has reached 0 and the bullet has exploded
  if(_explosionTime <= 0.f && _exploded) {
    //delete it
    _parent->setForDelete();

  }
}

//finds out if the bullet has hit an enemy
void BulletComponent::checkCollisions(const std::vector<const b2Contact*>& contacts) {
  //make sure there are contacts still
  if(contacts.size() > 0) {
    //check each enemy for collisions with the bullet
    for(auto enemy : _enemies) {
      //get necessary components
      auto enemyPhysics = enemy->GetCompatibleComponent<PhysicsComponent>()[0];
      const auto parentPhysics = _parent->get_components<PhysicsComponent>()[0];

      //if they are touching
      b2Contact* bc;
      if(parentPhysics->isTouching(*enemyPhysics, bc)) {
        //remove enemy
        enemyPhysics->setParentForDelete();
      } 
    }
  } 
}

//changes the animation to the explosion animation and starts the explosion counter
void BulletComponent::explode() {
  //change the animation
  auto ac = _parent->get_components<AnimatedSpriteComponent>()[0];
  ac->setSpritesheet(TextureManager::getTexture("explosion-2.png"));
  ac->setNumberOfFrames(8);
  ac->setCurrentRow(0);
  ac->setSpriteSheetPadding(0);

  //set exploded to true so we know it has exploded
  _exploded = true;
  //reset explosion time!!
  _explosionTime = 0.8f;
  //and life time
  _lifetime = 0.4f;

  //update the list of enemies!!
  _enemies = _parent->scene->ents.find("enemy");

}

//returns whether the bullet has exploded
bool BulletComponent::isExploded() const {
  return _exploded;
}

BulletComponent::BulletComponent(Entity* p, float lifetime)
    : Component(p), _lifetime(lifetime), _exploded(false), _explosionTime(0.5f) {
        _enemies = _parent->scene->ents.find("enemy");
    }

