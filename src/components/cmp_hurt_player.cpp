#include "cmp_hurt_player.h"
#include "cmp_player_lives.h"
#include "cmp_player_animated_sprite.h"
#include <engine.h>

using namespace std;
using namespace sf;

void HurtComponent::update(double dt) {
  if (auto pl = _player.lock()) {
    //cout << length(pl->getPosition() - _parent->getPosition()) << endl;
    auto anim = pl->get_components<PlayerAnimatedSpriteComponent>()[0];
    if ((length(pl->getPosition() - _parent->getPosition()) <= 49.0) && !anim->isHurt()) {
      auto lives = pl->get_components<PlayerLivesComponent>()[0];
      anim->setHurt(true);
      lives->decreaseLives(1);
      //_parent->setForDelete();
    }
  }
}

HurtComponent::HurtComponent(Entity* p)
    : Component(p), _player(_parent->scene->ents.find("player")[0]) {}