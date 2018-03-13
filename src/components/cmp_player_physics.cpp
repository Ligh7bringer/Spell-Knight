#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include "cmp_animated_sprite.h"
#include "../../engine/lib_ecm/ecm.h"
#include "cmp_player_bullet.h"
#include <SFML/Window/Keyboard.hpp>

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
      onTop &= (manifold.points[j].y < pos.y - halfPlrHeigt && manifold.points[j].x > pos.x - halfPlrWidth);
    }
    //change this so it makes sure edges are not considered collisions
    if(onTop) {
      return true;
    }
  }

  return false;
}

void PlayerPhysicsComponent::update(double dt) {
  _shooting = false;

  const auto pos = _parent->getPosition();

  //Teleport to start if we fall off map.
  if (pos.y > ls::getHeight() * ls::getTileSize()) {
	  cout << "no map left!!" << endl;
    teleport(ls::getTilePosition(ls::findTiles(ls::baseTiles::START)[0]));
  }

  if (Keyboard::isKeyPressed(Keyboard::A) ||
      Keyboard::isKeyPressed(Keyboard::D)) {
    // Moving Either Left or Right
    if (Keyboard::isKeyPressed(Keyboard::D)) {
      if (getVelocity().x < _maxVelocity.x) {
        impulse({(float)(dt * _groundspeed), 0});
        _direction = 1;
        _facing = true;
      }
    } else {
      if (getVelocity().x > -_maxVelocity.x) {
        impulse({-(float)(dt * _groundspeed), 0});
        _direction = -1;
        _facing = false;
      }
    }
  } else {
    // Dampen X axis movement
    dampen({0.9f, 1.0f});
    _direction = 0;
  }

  // Handle Jump
  if (Keyboard::isKeyPressed(Keyboard::W)) {
    _grounded = isGrounded();
    if (_grounded) {
      setVelocity(Vector2f(getVelocity().x, 0.f));
	  //temporary solution to the box jump bug
	  if (_body->GetPosition().y < 10.f)
	  {
		  teleport(Vector2f(pos.x, pos.y - 1.0f));
		  impulse(Vector2f(0, -8.f));
	  }
    }
  }

  //Are we in air?
  if (!_grounded) {
    // Check to see if we have landed yet
    _grounded = isGrounded();
    // disable friction while jumping
    setFriction(0.f);
  } else {
    setFriction(0.1f);
  }

  // Clamp velocity.
  auto v = getVelocity();
  v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
  v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
  setVelocity(v);

  //shoot, TODO: move this to a another component or somewhere else!!
  if(Keyboard::isKeyPressed(Keyboard::Space)) {
    _parent->get_components<PlayerBulletComponent>()[0]->fire();
    _shooting = true;
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
  _facing = true;
}

int PlayerPhysicsComponent::getDirection() const {
  return _direction;
}

bool PlayerPhysicsComponent::isJumping() const {
  return !_grounded;
}

bool PlayerPhysicsComponent::facingRight() const {
  return _facing;
}

bool PlayerPhysicsComponent::isShooting() const {
  return _shooting;
}