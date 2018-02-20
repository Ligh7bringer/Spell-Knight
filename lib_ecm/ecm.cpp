#include "ecm.h"

//Entity
Entity::Entity()
{
	_forDeletion = false;
	_points = 0;
}

void Entity::Update(double dt) {
	if (!is_forDeletion()) {
		for (auto &_c : _components) {
			if(!_c->is_forDeletion())
				_c->Update(dt);
		}
	}
	//std::cout << std::to_string(_points) << std::endl;
}

void Entity::Render()
{
	if (!_forDeletion) {
		for (auto &_c : _components) {
			if(!_c->is_forDeletion())
				_c->Render();
		}
	}
}

sf::Vector2f& Entity::getPosition()
{
	return _position;
}

void Entity::setPosition(const sf::Vector2f &pos) {
	_position = pos;
}

bool Entity::is_forDeletion() const
{
	return _forDeletion;
}

float Entity::getRotation() const
{
	return _rotation;
}

void Entity::setRotation(float _rot)
{
	_rotation = _rot;
}

bool Entity::isAlive() const
{
	return _alive;
}

void Entity::setAlive(bool _value)
{
	_alive = true;
}

void Entity::setForDelete()
{
	_forDeletion = true;
}

bool Entity::isVisible() const
{
	return _visible;
}

void Entity::setVisible(bool _value)
{
	_visible = _value;
}

//Component
Component::Component(Entity * p)
{
	_parent = p;
	_forDeletion = false;
}

bool Component::is_forDeletion()
{
	return _forDeletion;
}

void Component::setForDeletion() {
	_forDeletion = true;
}

Component::~Component()
{
}

//Entity Manager
void EntityManager::Render() {
	for (auto &_e : list) {
		_e->Render();
	}
}

void EntityManager::Update(double dt) {
	for (auto &e : list) {
		e->Update(dt);
	}
}
