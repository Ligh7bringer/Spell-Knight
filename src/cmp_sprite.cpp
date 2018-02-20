#include "cmp_sprite.h"
#include "system_renderer.h"
#include <iostream>

ShapeComponent::ShapeComponent(Entity *p) : Component(p), _shape(std::make_shared<sf::CircleShape>()) {}

void ShapeComponent::Update(double dt) {
	_shape->setPosition(_parent->getPosition());
}

void ShapeComponent::Render() {
	Renderer::queue(_shape.get());
}

sf::Shape& ShapeComponent::getShape() const {
	return *_shape;
}

