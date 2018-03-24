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