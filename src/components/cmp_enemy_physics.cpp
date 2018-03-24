#include "cmp_enemy_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include "cmp_animated_sprite.h"
#include "cmp_enemy_ai.h"
#include "../Log.h"
#include "cmp_actor_movement.h"

using namespace std;
using namespace sf;
using namespace Physics;

bool EnemyPhysicsComponent::isGrounded() const {
	auto touch = getTouching();
	const auto& pos = _body->GetPosition();
	const float halfPlrHeigt = _size.y * .25f;
	const float halfPlrWidth = _size.x * .25f;
	b2WorldManifold manifold;
	for (const auto& contact : touch) {
		contact->GetWorldManifold(&manifold);
		const int numPoints = contact->GetManifold()->pointCount;
		bool onTop = numPoints > 0;
		// If all contacts are below the enemy.
		for (int j = 0; j < numPoints; j++) {
			onTop &= (manifold.points[j].y < pos.y- halfPlrHeigt);
		}
		if (onTop) {
			return true;
		}
	}

	return false;
}

void EnemyPhysicsComponent::update(double dt) {

	// const auto pos = _parent->getPosition() ;
    // auto mov = _direction * (float)(dt * 100);
    // mov.x += _direction.x * 16.f;
	

	// //enemy falling off map
	// if (pos.y > ls::getHeight() * ls::getTileSize()) {
	// 	cout << "enemy has been affected by the forces of gravity!!" << endl;
	// 	//teleport(ls::getTilePosition(ls::findTiles(ls::baseTiles::START)[0]));
	// }

	// if(_isAir)
	// { 
	// 	//check if the creature is certain height above ground
	// 	if (isGrounded()) {
	// 		setVelocity(Vector2f(getVelocity().x, 0.f));
	// 		teleport(Vector2f(pos.x, pos.y - 1.0f));
	// 		impulse(Vector2f(0, -8.f));

	// 		// Dampen X axis movement
	// 		dampen({ 0.9f, 1.0f });
	// 		_direction = Vector2f(0,0);
	// 	}
	// }
	

	//Are we in air?
	if (!_grounded) {
		// Check to see if we have landed yet
		_grounded = isGrounded();
		// disable friction while jumping
		setFriction(0.f);
	}
	else {
		setFriction(0.1f);
	}

	// Clamp velocity.
	auto v = getVelocity();
	v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
	v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
	setVelocity(v);

	PhysicsComponent::update(dt);
}

EnemyPhysicsComponent::EnemyPhysicsComponent(Entity* p,
	const Vector2f& size, bool isAir)
	: PhysicsComponent(p, true, size) {
	_size = sv2_to_bv2(size, true);
	_isAir = isAir;
	_maxVelocity = Vector2f(200.f, 400.f);
	_direction = Vector2f(1,0);
	_groundspeed = 30.f;
	_grounded = false;
	_body->SetSleepingAllowed(false);
	_body->SetFixedRotation(true);
	//Bullet items have higher-res collision detection
	_body->SetBullet(false);
}

sf::Vector2f EnemyPhysicsComponent::getDirection() const {
	return _direction;
}

bool EnemyPhysicsComponent::isJumping() const {
	return !_grounded;
}

void EnemyPhysicsComponent::setAir(bool b) {
	_isAir = b;
}