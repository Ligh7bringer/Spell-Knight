#include "cmp_enemy_ai.h"
#include "cmp_physics.h"

using namespace std;
using namespace sf;

void EnemyAIComponent::update(double dt) { }

EnemyAIComponent::EnemyAIComponent(Entity* p)
	: ActorMovementComponent(p)
{
	_direction = Vector2f(1.0f, 0);
	_speed = 10.f;
}

float EnemyAIComponent::getSpeed() const { return _speed; }

Vector2f EnemyAIComponent::getDirection() { return _direction; }