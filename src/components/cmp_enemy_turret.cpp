#include "cmp_enemy_turret.h"
#include "cmp_turret_bullet.h"
#include "cmp_hurt_player.h"
#include "cmp_animated_sprite.h"
#include "../../engine/lib_texture_manager/TextureManager.h"
#include "engine.h"

using namespace std;
using namespace sf;

void EnemyTurretComponent::update(double dt) {
  _firetime -= dt;
  
  if (_firetime <= 0.f) {
    fire();
    _firetime = 2.f;
  }
}

void EnemyTurretComponent::fire() const {
  //create bullet
  auto bullet = _parent->scene->makeEntity();
  bullet->setPosition(_parent->getPosition() + _offset);
  bullet->addComponent<HurtComponent>();
  bullet->addComponent<TurretBulletComponent>();
  //add a sprite
  auto sprite = bullet->addComponent<AnimatedSpriteComponent>(Vector2f(32.f, 32.f));
  sprite->setNumberOfFrames(5);
  sprite->setCurrentRow(4);
  sprite->setSpriteSheetPadding(2);
  sprite->setSpritesheet(TextureManager::getTexture("projectiles.png"));
  
  //add physics component
  auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(32.f, 32.f));
  p->setRestitution(.4f);
  p->setFriction(.005f);
  p->impulse(sf::rotate(Vector2f(7.f, 8.f) * _direction, -_parent->getRotation()));
}

EnemyTurretComponent::EnemyTurretComponent(Entity* p)
    : Component(p), _firetime(2.f), _offset(Vector2f(-32.f, -16.f)), _direction(Vector2f(-1.f, 1.f)) {}
