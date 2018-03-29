#pragma once
#include "cmp_physics.h"
#include <ecm.h>

using namespace sf;

class EnemyTurretComponent : public Component {
protected:
  void fire() const;
  float _firetime;
  sf::Vector2f _offset;
  sf::Vector2f _direction;
  std::weak_ptr<Entity> _player;
  float _rotationCooldown;

public:
  void update(double dt) override;
  void render() override {}
  explicit EnemyTurretComponent(Entity* p);
    void setDirection(const sf::Vector2f& direction);
    void setOffset(const Vector2f& offset);
  EnemyTurretComponent() = delete;
};
