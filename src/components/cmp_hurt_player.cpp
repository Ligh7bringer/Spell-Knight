#include "cmp_hurt_player.h"
#include "cmp_player_lives.h"
#include "cmp_player_animated_sprite.h"
#include <engine.h>

using namespace std;
using namespace sf;

void HurtComponent::update(double dt) {
  if (auto pl = _player.lock()) {
    //get necessary components
    auto anim = pl->get_components<PlayerAnimatedSpriteComponent>()[0];
    auto playerPhysics = pl->GetCompatibleComponent<PhysicsComponent>()[0];
    auto parentPhysics = _parent->GetCompatibleComponent<PhysicsComponent>()[0];
    auto touching = parentPhysics->getTouching();

    //check for minimum distance between the entities before using the box2d method of collision detection
    if(length(_parent->getPosition() - pl->getPosition()) < 69.f) { 
      //if the entities are colliding
      if (touching.size() > 0 && parentPhysics->isTouching(*playerPhysics) && !anim->isHurt()) {
        //change the player animation
        auto lives = pl->get_components<PlayerLivesComponent>()[0];
        anim->setHurt(true);
        //decrease the player's lives
        lives->decreaseLives(1);
      }
    }
  }
}

HurtComponent::HurtComponent(Entity* p)
    : Component(p), _player(_parent->scene->ents.find("player")[0]) {}