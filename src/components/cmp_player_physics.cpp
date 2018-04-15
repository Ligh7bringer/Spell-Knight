#include "cmp_player_physics.h"
#include <LevelSystem.h>
#include "cmp_animated_sprite.h"
#include "cmp_player_attack.h"
#include "../../engine/lib_input_manager/input_manager.h"

using namespace std;
using namespace sf;
using namespace Physics;

bool PlayerPhysicsComponent::isGrounded() const {
  auto touch = getTouching();
  const auto& pos = _body->GetPosition();
  const float halfPlrHeigt = _size.y * .5f;
  const float halfPlrWidth = _size.x * .5f;
  b2WorldManifold manifold;
  for (const auto& contact : touch) {
    contact->GetWorldManifold(&manifold);
    const int numPoints = contact->GetManifold()->pointCount;
    bool onTop = numPoints > 1;
    // If all contacts are below the player.
    for (int j = 0; j < numPoints; j++) {
      onTop &= (manifold.points[j].y < pos.y - halfPlrHeigt);
    }
    //change this so it makes sure edges are not considered collisions
    if(onTop) {
      return true;
    }
  }

  return false;
}

void PlayerPhysicsComponent::update(double dt) {
  auto anim = _parent->get_components<AnimatedSpriteComponent>()[0];

  const auto pos = _parent->getPosition();

  if (pos.y > ls::getHeight() * ls::getTileSize()) {
    _parent->setAlive(false);
  }

  if (Keyboard::isKeyPressed(InputManager::getKey("walkLeft")) ||
      Keyboard::isKeyPressed(InputManager::getKey("walkRight"))) {
    // Moving Either Left or Right
    if (Keyboard::isKeyPressed(InputManager::getKey("walkRight"))) {
      if (getVelocity().x < _maxVelocity.x) {
        impulse({(float)(dt * _groundspeed*2.f), 0.01f});

        //play walking right animation
        anim->setFacingRight(true);
        anim->setCurrentRow(1);
      }
    } else {
      if (getVelocity().x > -_maxVelocity.x) {
        impulse({-(float)(dt * _groundspeed*2.f), 0.01f});

        //play walking left animation
        anim->setFacingRight(false);
        anim->setCurrentRow(1);
      }
    }
  } else {
    // Dampen X axis movement
    dampen({0.9f, 1.0f});
    
    //play idle animation
    anim->setCurrentRow(0);
  }
  
  // Handle Jump
  if (Keyboard::isKeyPressed(InputManager::getKey("jump"))) {
    _grounded = isGrounded();
    //play jumping animation
    anim->setCurrentRow(2);
    //anim->stallAnimation(2);

    if (_grounded) {
      setVelocity(Vector2f(getVelocity().x, 0.f));
      //play idle animation
      anim->setCurrentRow(0);
      teleport(Vector2f(pos.x, pos.y - 1.0f));
      impulse(Vector2f(0.f, -8.f));      
    }
  }

  //Are we in air?
  if (!_grounded) {
    // Check to see if we have landed yet
    _grounded = isGrounded();
    // disable friction while jumping
    setFriction(0.f);
  } else {
    setFriction(0.01f);
  }

  // Clamp velocity.
  auto v = getVelocity();
  v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
  v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
  setVelocity(v);

  //shoot
  if(Keyboard::isKeyPressed(InputManager::getKey("shoot"))) {
    //play shooting animation
    anim->lockInAnimation(3);
    _parent->get_components<PlayerAttackComponent>()[0]->fire();
  }

  PhysicsComponent::update(dt);
}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p, 
                                               const Vector2f& size)
    : PhysicsComponent(p, true, size) {
  _size = sv2_to_bv2(size, true);
  _maxVelocity = Vector2f(200.f, 400.f);
  _groundspeed = 30.f;
  _grounded = false;
  _body->SetSleepingAllowed(false);
  _body->SetFixedRotation(true);
  //Bullet items have higher-res collision detection
  _body->SetBullet(true);
}