#include "bird_states.h"
#include "../components/cmp_animated_sprite.h"
#include "../components/cmp_enemy_physics.h"
#include "../Log.h"
#include "../../engine/lib_texture_manager/TextureManager.h"
#include "../components/cmp_ai_steering.h"
#include "LevelSystem.h"

/*
* Behaviour of the flying cloud.
*/

using namespace sf;

// ----- Flying state -----
//FlyingState::FlyingState() : _direction(Vector2f(1,0)) {}

void FlyingbirdState::execute(Entity* owner, double dt) noexcept {

  if (_setup) {
    auto anim = owner->get_components<AnimatedSpriteComponent>()[0];
    anim->setSpritesheet(TextureManager::getTexture("lightning_1.png"));
    anim->setNumberOfFrames(1);
    _setup = false;
  }
  auto physics = owner->GetCompatibleComponent<PhysicsComponent>()[0];
  auto anim = owner->get_components<AnimatedSpriteComponent>()[0];
  auto steer = owner->get_components<SteeringComponent>()[0];

  physics->impulse(Vector2f(steer->getOutput().xdirection,0) * (float)(dt));
}
