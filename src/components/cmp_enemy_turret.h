#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include <SFML/Graphics/CircleShape.hpp>

class EnemyTurretComponent : public Component {
protected:
  void fire() const;
  float _firetime;

public:
  void update(double dt) override;
  void render() override {}
  explicit EnemyTurretComponent(Entity* p);
  EnemyTurretComponent() = delete;
};
