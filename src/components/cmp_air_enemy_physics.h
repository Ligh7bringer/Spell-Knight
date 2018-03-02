#pragma once

#include "cmp_physics.h"

class AirEnemyPhysicsComponent : public PhysicsComponent {
protected:
	b2Vec2 _size;
	sf::Vector2f _maxVelocity;
	bool _grounded;
	float _groundspeed;
	int _direction;

	bool isGrounded() const;

public:
	void update(double dt) override;

	explicit AirEnemyPhysicsComponent(Entity* p, const sf::Vector2f& size);

	AirEnemyPhysicsComponent() = delete;

	int getDirection() const;

	bool isJumping() const;
};
