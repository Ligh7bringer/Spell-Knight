#include "bird_states.h"
#include "../components/cmp_animated_sprite.h"
#include "../components/cmp_enemy_physics.h"
#include "../Log.h"
#include "../../engine/lib_texture_manager/TextureManager.h"
#include "../components/cmp_ai_steering.h"
#include "LevelSystem.h"

/*
* Behaviour of the flying eye creature.
*/

using namespace sf;

// ----- Roaming state ------
void SleepingbirdState::execute(Entity* owner, double dt) noexcept {
  auto physics = owner->GetCompatibleComponent<PhysicsComponent>()[0];
  auto anim = owner->get_components<AnimatedSpriteComponent>()[0];

  const auto pos = owner->getPosition() ;
  auto mov = _direction * (float)(dt * 100);
  mov.x += _direction.x * 16.f;

  if(LevelSystem::getTileAt(pos + mov) == '2' || LevelSystem::getTileAt(pos + mov) == '0'){
    _direction *= -1.f;
  }

  physics->impulse(_direction * (float)(dt*100));
  anim->setFacingRight(_direction.x > 0);
}

// ----- Flying state -----
//FlyingState::FlyingState() : _direction(Vector2f(1,0)) {}

void FlyingbirdState::execute(Entity* owner, double dt) noexcept {

  if (_setup) {
    auto anim = owner->get_components<AnimatedSpriteComponent>()[0];
    anim->setSpritesheet(TextureManager::getTexture("eyeflying.png"));
    anim->setNumberOfFrames(4);
    _setup = false;
  }
  auto physics = owner->GetCompatibleComponent<PhysicsComponent>()[0];
  auto anim = owner->get_components<AnimatedSpriteComponent>()[0];
  auto steer = owner->get_components<SteeringComponent>()[0];

  physics->impulse(Vector2f(steer->getOutput().xdirection,0) * (float)(dt));
  anim->setFacingRight(steer->getOutput().xdirection>0);
}
