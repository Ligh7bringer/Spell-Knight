#include "cmp_bullet.h"
#include "cmp_player_bullet.h"
#include "cmp_animated_sprite.h"
#include "../../engine/lib_texture_manager/TextureManager.h"
#include "system_physics.h"
#include "../../engine/src/engine.h"
#include "../../engine/lib_ecm/ecm.h"
#include <iostream>

using namespace std;
using namespace sf;

void BulletComponent::update(double dt) {
  //get the collisions from the physics component
  auto touching = _parent->get_components<PhysicsComponent>()[0]->getTouching();

  _lifetime -= dt;
  //timer to set a delay so the whole explosion animation can be played before the bullet is destroyed
  _explosionTime -= dt;

  //if its touching anything or its lifetime counter has reached 0
  if (_lifetime <= 0.f || touching.size() > 0) {    
    //and the bullet hasn't exploded yet
    if(!_exploded) {
      //change the animation
      auto ac = _parent->get_components<AnimatedSpriteComponent>()[0];
      ac->setSpritesheet(TextureManager::getTexture("explosion-2.png"));
      ac->setNumberOfFrames(8);
      ac->setCurrentRow(0);
      ac->setSpriteSheetPadding(0);

      //set exploded to true so we know it has exploded
      _exploded = true;
      //reset explosion time!!
      _explosionTime = 0.5f;
      //and life time
      _lifetime = 1.0f;
    }
    
    //if the "timer" has reached 0 and the bullet has exploded
    if(_explosionTime <= 0.f && _exploded) {
      //delete it
      _parent->setForDelete();
      // auto pl = _parent->scene->ents.find("player")[0];
      // auto pbc = pl->get_components<PlayerBulletComponent>()[0];
      // pbc->removeBullet(shared);
    }
  } 
}

BulletComponent::BulletComponent(Entity* p, float lifetime)
    : Component(p), _lifetime(lifetime), _exploded(false), _explosionTime(0.5f) {}
