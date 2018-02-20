#include "cmp_actor_movement.h"

using namespace sf;
//ACTOR MOVEMENT
void ActorMovementComponent::Render() {}

void ActorMovementComponent::Update(double dt) {}

ActorMovementComponent::ActorMovementComponent(Entity *p) : _speed(100.0f), Component(p) {}

bool ActorMovementComponent::validMove(const sf::Vector2f &pos) {
	return true;
}

void ActorMovementComponent::move(const Vector2f &p) {
	auto pp = _parent->getPosition() + p;
	if (validMove(pp)) {
		_parent->setPosition(pp);
	}
}

void ActorMovementComponent::move(float x, float y) {
	move(Vector2f(x, y));
}

float ActorMovementComponent::getSpeed() const {
	return _speed;
}

void ActorMovementComponent::setSpeed(float speed) {
	_speed = speed;
}

void ActorMovementComponent::increaseSpeed(float speed) {
	_speed += speed;
}

//PLAYER MOVEMENT COMPONENT
PlayerMovementComponent::PlayerMovementComponent(Entity *p) : ActorMovementComponent(p) {}

void PlayerMovementComponent::Update(double dt) {
	int xdir = 0, ydir = 0;
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		move(Vector2f(0, -_speed * dt));
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		move(Vector2f(0, _speed * dt));
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		move(Vector2f(-_speed * dt, 0));
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		move(Vector2f(_speed * dt, 0));
	}

	ActorMovementComponent::Update(dt);
}

void PlayerMovementComponent::Render() {
	ActorMovementComponent::Render();
}

