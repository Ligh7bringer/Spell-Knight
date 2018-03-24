#pragma once

#include "cmp_physics.h"

class EnemyPhysicsComponent : public PhysicsComponent {
protected:
	b2Vec2 _size;
	sf::Vector2f _maxVelocity;
	bool _grounded;
	float _groundspeed;
	sf::Vector2f _direction;
	bool _isAir; 

public:
	void update(double dt) override;

	explicit EnemyPhysicsComponent(Entity* p, const sf::Vector2f& size, bool isAir);

	EnemyPhysicsComponent() = delete;

	sf::Vector2f getDirection() const;

	bool isJumping() const;

	void setAir(bool b);

	bool isGrounded() const;
};
