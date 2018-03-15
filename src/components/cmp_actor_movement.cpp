#include "cmp_actor_movement.h"
#include "cmp_animated_sprite.h"
#include <LevelSystem.h>
#include <engine.h>
#include <iostream>

using namespace sf;
using namespace std;

void ActorMovementComponent::update(double dt) {}

ActorMovementComponent::ActorMovementComponent(Entity* p)
    : _speed(100.0f), Component(p) {}

bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
	return (LevelSystem::getTileAt(pos) != '1' && ls::getTileAt(pos)!= '2' && ls::getTileAt(pos)!='3'
		&& LevelSystem::getTileAt(pos) != '4' && ls::getTileAt(pos) != '5' && ls::getTileAt(pos) != '6'
		&& LevelSystem::getTileAt(pos) != '7' && ls::getTileAt(pos) != '8' && ls::getTileAt(pos) != '9'
		&& LevelSystem::getTileAt(pos) != '0'
		&& LevelSystem::getTileAt(pos) != 'I' && ls::getTileAt(pos) != 'O' && ls::getTileAt(pos) != 'P');
}

void ActorMovementComponent::move(const sf::Vector2f& p) {
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