#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class BulletComponent : public Component {
protected:
  float _lifetime;
  float _explosionTime;
  bool _exploded;
  int _damage;
  void checkCollisions(const std::vector<const b2Contact*>& contacts);
  std::vector<std::shared_ptr<Entity>> _enemies;
  std::weak_ptr<Entity> _player;
  void explode();

public:
  void update(double dt) override;
  void render() override {}
  bool isExploded() const;

  explicit BulletComponent(Entity* p, float lifetime = 3.f);
  BulletComponent() = delete;

  void setDamage(int dmg);
  int getDamage() const;
};
