#include "cmp_enemy_ai.h"
#include "cmp_physics.h"

using namespace std;
using namespace sf;

void EnemyAIComponent::update(double dt) {
  // auto cmp = _parent->get_components<PhysicsComponent>()[0];
  // //cout << cmp->getTouching().size() << endl;

  // if(cmp->getTouching().size() > 1) {
  //   //cout << cmp->getLinearVelocity().x << endl;
  //   //cmp->setLinearVelocity(Vector2f(cmp->getLinearVelocity().x * -1.f * _speed, 0));
  //   _speed = cmp->getLinearVelocity().x;
  //   _speed *= -1;
  //   cout << _speed << endl;
  //   cmp->impulse(Vector2f(_speed * dt, 0));
  //   //cmp->teleport(Vector2f(-5.f, 0));
  // }

  auto mov = _direction * (float)(dt * _speed);
  mov.x += _direction.x * 16.f;
  if (!validMove(_parent->getPosition() + mov)) {
    _direction *= -1.f;
	//cout << _direction << endl;
  }

  move(_direction * (float)(dt * _speed));
  ActorMovementComponent::update(dt);
}

EnemyAIComponent::EnemyAIComponent(Entity* p) : ActorMovementComponent(p) {
  _direction = Vector2f(1.0f, 0);
  _speed = 10.f;
}

float EnemyAIComponent::getSpeed() const {
  return _speed;
}

Vector2f EnemyAIComponent::getDirection() {
  return _direction;
}