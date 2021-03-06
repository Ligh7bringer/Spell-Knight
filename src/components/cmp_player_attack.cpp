#include "cmp_player_attack.h"
#include "../Log.h"
#include "cmp_animated_sprite.h"
#include "cmp_bullet.h"
#include "cmp_particles.h"
#include "engine.h"
#include "texture_manager.h"

using namespace sf;

/*
* This component allows the player to shoot.
*/

//set spritesheet, position of bullet relative to player, speed of bullet
PlayerAttackComponent::PlayerAttackComponent(Entity* p)
	: Component(p)
	, _cooldown(1.f)
{
	//_spritesheet = TextureManager::getTexture("WIZARD.png");
	//this offset is needed because the bullet shouldn't be spawned on top of the player, but next to them
	_posOffset = Vector2f(35.f, 5.f);
	_speed = 10.f;
	_cooldown = 0;

	initAttacks();
	changeAttack(DEFAULT);
	_lastAttack = _currentAttack;
}

//don't need to render anything (at the moment)
void PlayerAttackComponent::render() { }

//creates a bullet
void PlayerAttackComponent::fire()
{
	//make sure the current attack is not on cooldown
	if(_cooldown <= 0.0f)
	{
		//find out which way the player is facing
		auto right = _parent->get_components<AnimatedSpriteComponent>()[0]->isFacingRight();
		//auto right = true;
		auto offset = _posOffset;

		//invert the offset if the player is facing left
		if(!right) offset.x = -offset.x;

		//create bullet, set its position to the left/right of the player and add a bullet component
		auto bullet = _parent->scene->makeEntity();
		bullet->setPosition(_parent->getPosition() + offset);
		auto bulletComp = bullet->addComponent<BulletComponent>();
		bulletComp->setDamage(_currentAttack.damage);

		auto sprite = bullet->addComponent<AnimatedSpriteComponent>(_currentAttack.spriteSize);
		sprite->setCurrentRow(_currentAttack.row);
		sprite->setSpritesheet(TextureManager::getTexture(_currentAttack.spriteSheet));
		sprite->setNumberOfFrames(_currentAttack.frameCount);
		sprite->setFrameTime(0.15f);
		sprite->setFacingRight(right);

		//add a physics component
		auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(32.f, 32.f));
		//the bullet shouldn't be affected by gravity
		p->setGravityScale(0.0f);
		p->setRestitution(0);
		p->setFriction(.005f);
		//set the appropriate direction
		p->setLinearVelocity(right ? Vector2f(_speed, 0) : Vector2f(-_speed, 0));

		//create a smoke trail effect for the fireball
		if(_currentAttack.type == FIREBALL)
		{
			auto ps =
				bullet->addComponent<ParticleSystemComponent>(ParticleSystem::TRAIL, "smoke.png");
			ps->setColour(sf::Color(192, 192, 192));
			ps->setEmissionRate(100.0f);
			ps->setLifetime(1.f);
		}

		_cooldown = _currentAttack.cooldown;

		AudioManager::playSound(_currentAttack.sound);
	}
}

void PlayerAttackComponent::update(double dt)
{
	//update cooldown
	_cooldown -= dt;
}

void PlayerAttackComponent::initAttacks()
{
	//fireball attack
	Attack fireball;
	fireball.type = FIREBALL;
	fireball.damage = 4;
	fireball.cooldown = 1.6f;
	fireball.spriteSize = Vector2f(64.f, 22.f);
	fireball.spriteSheet = "fireball2.png";
	fireball.frameCount = 8;
	fireball.row = 0;
	fireball.sound = "fireball.wav";
	_availableAttacks.push_back(fireball);

	//default attack
	Attack normal;
	normal.type = DEFAULT;
	normal.damage = 1;
	normal.cooldown = 1.0f;
	normal.spriteSize = Vector2f(32.f, 32.f);
	normal.spriteSheet = "projectiles2.png";
	normal.frameCount = 6;
	normal.row = 4;
	normal.sound = "shoot.wav";
	_availableAttacks.push_back(normal);

	//icicle attack
	Attack icicle;
	icicle.type = ICICLE;
	icicle.damage = 2;
	icicle.cooldown = 1.2f;
	icicle.spriteSize = Vector2f(64.f, 45.f);
	icicle.spriteSheet = "icicle.png";
	icicle.frameCount = 8;
	icicle.row = 0;
	icicle.sound = "shoot.wav";
	_availableAttacks.push_back(icicle);

	//shock attack
	Attack shock;
	shock.type = SHOCK;
	shock.damage = 3;
	shock.cooldown = 1.4f;
	shock.spriteSize = Vector2f(64.f, 45.f);
	shock.spriteSheet = "shock.png";
	shock.frameCount = 4;
	shock.row = 0;
	shock.sound = "shock.wav";
	_availableAttacks.push_back(shock);
}

PlayerAttackComponent::Attack& PlayerAttackComponent::getAttack(int p)
{
	return _availableAttacks[p];
}

void PlayerAttackComponent::changeAttack(AttackType at)
{
	for(auto attack : _availableAttacks)
	{
		if(attack.type == at)
		{
			_lastAttack = _currentAttack;
			_currentAttack = attack;
			LOG(INFO) << "Changing player attack to " << attack.type;
		}
	}
}

PlayerAttackComponent::AttackType PlayerAttackComponent::getAttackType() const
{
	return _currentAttack.type;
}
