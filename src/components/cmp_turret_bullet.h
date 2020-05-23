#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class TurretBulletComponent : public Component
{
protected:
	float _lifetime;

public:
	void update(double dt) override;
	void render() override { }
	explicit TurretBulletComponent(Entity* p, float lifetime = 3.f);
	TurretBulletComponent() = delete;
};