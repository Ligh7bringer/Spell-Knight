#include "cmp_bullet.h"
#include "cmp_player_bullet.h"
#include "cmp_physics.h"
#include "cmp_animated_sprite.h"
#include "cmp_enemy_physics.h"
#include "../../engine/lib_texture_manager/TextureManager.h"
#include "system_physics.h"
#include "../../engine/src/engine.h"
#include "../../engine/lib_ecm/ecm.h"
#include "cmp_score.h"
#include "cmp_enemy_health.h"
#include "../../engine/src/system_renderer.h"
#include "../Log.h"

using namespace std;
using namespace sf;

/*
* This component, when attached to a bullet entity, handles its lifetime and collisions.
*/
BulletComponent::BulletComponent(Entity* p, float lifetime)
	: Component(p), _lifetime(lifetime), _player(_parent->scene->ents.find("player")[0]), _exploded(false), _explosionTime(0.5f), _enemies(_parent->scene->ents.find("enemy")) {}
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
  //get necessary component
  const auto parentPhysics = _parent->get_components<PhysicsComponent>()[0];

  //get player component to set the players score based on enemy's death
  //make sure the bullet is still colliding with something
  if(contacts.size() > 0) {
    //check each enemy for collisions with the bullet
    for(auto enemy : _enemies) {
      //get bounds of enemy sprite
      auto anim = enemy->get_components<AnimatedSpriteComponent>()[0];
      auto bounds = anim->getSprite().getGlobalBounds();
      //check for collision if enemy is in the view
      if(Renderer::isInView(bounds)) {
        //get enemy physics component, have to use GetCompatibleComponent because enemies have an EnemyPhysicsComponent
        auto enemyPhysics = enemy->GetCompatibleComponent<PhysicsComponent>()[0];
      
        //if they are colliding
        if(parentPhysics->isTouching(*enemyPhysics)) {
          if(auto plr = _player.lock()) {
            auto score = plr->get_components<PlayerScoreComponent>()[0];
            //delete enemy
            auto enemyHealth = enemy->get_components<EnemyHealthComponent>()[0];
            //this hardocoded damage will become something like
            //plr->getWeaponDamage() when we add power ups
            enemyHealth->decreaseHealth(1);
            score->increasePoints(30);
            //update the list of enemies!!
            _enemies = _parent->scene->ents.find("enemy");
            break;
          }
        }          
      }
    }
  }

} 

//changes the animation to the explosion animation and starts the explosion counter
void BulletComponent::explode() {
  //change the animation
  auto ac = _parent->get_components<AnimatedSpriteComponent>()[0];
  ac->setSpritesheet(TextureManager::getTexture("explosion.png"));
  ac->setSize(Vector2f(32.f, 32.f));
  ac->setNumberOfFrames(8);
  ac->setCurrentRow(0);
  ac->setFrameTime(0.09f);

  //set exploded to true so we know it has exploded
  _exploded = true;
  //reset explosion time!!
  _explosionTime = (float)ac->getFrameCount() / 2 * ac->getFrameTime();
  //and life time
  _lifetime = 0.8f;
}

//returns whether the bullet has exploded
bool BulletComponent::isExploded() const {
  return _exploded;
}



