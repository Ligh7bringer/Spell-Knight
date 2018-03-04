#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class BulletComponent : public Component {
protected:
  float _lifetime;
  float _explosionTime;
  bool _exploded;
  void checkCollisions(const std::vector<const b2Contact*>& contacts);
  std::vector<std::shared_ptr<Entity>> _enemies;
  void explode();

public:
  void update(double dt) override;
  void render() override {}
  bool isExploded() const;

  explicit BulletComponent(Entity* p, float lifetime = 3.f);
  BulletComponent() = delete;
};
