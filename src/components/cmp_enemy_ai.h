#pragma once

#include "cmp_actor_movement.h"

class EnemyAIComponent : public ActorMovementComponent
{
protected:
	sf::Vector2f _direction;

public:
	void update(double dt) override;

	explicit EnemyAIComponent(Entity* p);

	float getSpeed() const;

	sf::Vector2f getDirection();

	EnemyAIComponent() = delete;
};
