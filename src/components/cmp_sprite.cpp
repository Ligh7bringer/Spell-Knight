
#include "cmp_sprite.h"
#include "system_renderer.h"

using namespace std;

SpriteComponent::SpriteComponent(Entity* p)
    : Component(p), _sprite(make_shared<sf::Sprite>()) {}

void SpriteComponent::update(double dt) {
  _sprite->setPosition(_parent->getPosition());
  _sprite->setRotation(_parent->getRotation());
}

void SpriteComponent::render() { Renderer::queue(_sprite.get()); }

void ShapeComponent::update(double dt) {
  _shape->setPosition(_parent->getPosition());
  _shape->setRotation(_parent->getRotation());
}

void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p)
    : Component(p), _shape(make_shared<sf::CircleShape>()) {}

sf::Sprite& SpriteComponent::getSprite() const { return *_sprite; }
