#include "cmp_enemy_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include "cmp_animated_sprite.h"
#include "cmp_enemy_ai.h"
#include "../Log.h"

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

	const auto pos = _parent->getPosition();
	

	//enemy falling off map
	if (pos.y > ls::getHeight() * ls::getTileSize()) {
		cout << "enemy has been affected by the forces of gravity!!" << endl;
		//teleport(ls::getTilePosition(ls::findTiles(ls::baseTiles::START)[0]));
	}

	if (!_isAir)
	{
		auto c = _parent->get_components<EnemyAIComponent>()[0];
		auto dir = c->getDirection();

		// Handle Jump
		//check if the creature is certain height above ground
		/*if (isGrounded()) {
			setVelocity(Vector2f(getVelocity().x, 0.f));
			teleport(Vector2f(pos.x, pos.y - 1.0f));
			impulse(Vector2f(0, -8.f));

			// Dampen X axis movement
			//dampen({ 0.9f, 1.0f });
			//_direction = 0;
		}*/

		switch (_state)
		{
		case ROAMING:
			LOG(DEBUG) << "ROAMING";
			//find the nextpos and compare with currentpos and if the tile types are different then chage state to rotating
			if (LevelSystem::getTileAt(Vector2f(pos.x + (_direction*dt +_groundspeed), pos.y)) != LevelSystem::getTileAt(pos)) {
				_state = ROAMING;
			}
			else
			{
				//if the tile types are the same then head in the same direction
				if (getVelocity().x < _maxVelocity.x) {
					cout << "impulse" << endl;
					impulse({ _direction*(float)(dt* _groundspeed),0 });
				}
			}
			break;
		case ROTATING:
			cout << "ROTATING" << endl;
			//if the current tile is not equal to the next tile then change the direction 
			if (LevelSystem::getTileAt(Vector2f(pos.x + (_direction*dt+_groundspeed), pos.y)) != LevelSystem::getTileAt(pos)) {
				_direction *= -1;
			}
			_state = ROTATED;
			break;
		case ROTATED:
			LOG(DEBUG) << "ROTATED";
			//put back to roaming if the nexttile is not the same as the current and impulse in an opposite direction
			if (LevelSystem::getTileAt(Vector2f(pos.x + (_direction*dt+_groundspeed), pos.y)) == LevelSystem::getTileAt(pos)) {
				if (getVelocity().x < _maxVelocity.x) {
					cout << "impoulse" << endl;
					impulse({ _direction*(float)(dt* _groundspeed),0 });
				}
				_state = ROAMING;
			}
			
			break;
		}
		/*
		if (dir == Vector2f(1.f, 0.f) ||
			dir == Vector2f(-1.f, 0.f)) {
			// Moving Either Left or Right
			if (dir == Vector2f(1.f, 0.f)) {
				//cout << "enemy going right" << endl;
				if (getVelocity().x < _maxVelocity.x) {
					impulse({ (float)(dt * _groundspeed), 0 });
					_direction = 1;
				}
			}
			else {
				//cout << "enemy going left" << endl;
				if (getVelocity().x > -_maxVelocity.x) {
					impulse({ -(float)(dt * _groundspeed), 0 });
					_direction = -1;
				}
			}
		}
		else {
			// Dampen X axis movement
			dampen({ 0.9f, 1.0f });
			//_direction = 0;
		}
	*/	
	}
	
	else
	{ 
		// Handle Jump
		//check if the creature is certain height above ground
		if (isGrounded()) {
			setVelocity(Vector2f(getVelocity().x, 0.f));
			teleport(Vector2f(pos.x, pos.y - 1.0f));
			impulse(Vector2f(0, -8.f));

			// Dampen X axis movement
			dampen({ 0.9f, 1.0f });
			_direction = 0;
		}
	}
	

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
	_direction = -1;
	_state = ROAMING;
	_groundspeed = 30.f;
	_grounded = false;
	_body->SetSleepingAllowed(false);
	_body->SetFixedRotation(true);
	//Bullet items have higher-res collision detection
	_body->SetBullet(false);
}

int EnemyPhysicsComponent::getDirection() const {
	return _direction;
}

bool EnemyPhysicsComponent::isJumping() const {
	return !_grounded;
}