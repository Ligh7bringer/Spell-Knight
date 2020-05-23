#include "cmp_enemy_turret.h"
#include "../Log.h"
#include "cmp_animated_sprite.h"
#include "cmp_hurt_player.h"
#include "cmp_turret_bullet.h"
#include "engine.h"
#include "texture_manager.h"

using namespace std;
using namespace sf;

void EnemyTurretComponent::update(double dt)
{
	_firetime -= dt;

	if(_firetime <= 0.f)
	{
		fire();
		_firetime = 2.f;
	}
}

void EnemyTurretComponent::fire() const
{
	//create bullet
	auto bullet = _parent->scene->makeEntity();
	bullet->setPosition(_parent->getPosition() + _offset);
	bullet->addComponent<HurtComponent>();
	bullet->addComponent<TurretBulletComponent>();

	//add a sprite
	auto sprite = bullet->addComponent<AnimatedSpriteComponent>(Vector2f(32.f, 32.f));
	sprite->setNumberOfFrames(5);
	sprite->setCurrentRow(4);
	sprite->setSpriteSheetPadding(0);
	sprite->setSpritesheet(TextureManager::getTexture("projectiles.png"));

	//add physics component
	auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(32.f, 32.f));
	p->setRestitution(.4f);
	p->setFriction(.005f);
	p->impulse(Vector2f(1.f, 1.f) * _direction);
}

EnemyTurretComponent::EnemyTurretComponent(Entity* p)
	: Component(p)
	, _firetime(2.f)
	, _player(_parent->scene->ents.find("player")[0])
	, _rotationCooldown(10.f)
{
	_direction = Vector2f(0.f, 0.f);
	_offset = Vector2f(-45.f, -16.f);
}

void EnemyTurretComponent::setDirection(const Vector2f& direction) { _direction = direction; }

void EnemyTurretComponent::setOffset(const Vector2f& offset) { _offset = offset; }
