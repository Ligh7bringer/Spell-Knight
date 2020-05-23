#include "cmp_turret_bullet.h"
using namespace std;
using namespace sf;

void TurretBulletComponent::update(double dt)
{
	_lifetime -= dt;
	if(_lifetime <= 0.f)
	{
		_parent->setForDelete();
	}
}

TurretBulletComponent::TurretBulletComponent(Entity* p, float lifetime)
	: Component(p)
	, _lifetime(lifetime)
{ }