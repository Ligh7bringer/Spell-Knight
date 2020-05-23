#pragma once
#include <engine.h>

//output from a steering behaviour
struct SteeringOutput
{
	//direction of travel
	float xdirection;
};

class SteeringBehaviour
{
public:
	virtual ~SteeringBehaviour() = default;

	//gets the output form a steering behaviour
	virtual SteeringOutput getSteering() const noexcept = 0;
};

class Seek : public SteeringBehaviour
{
private:
	Entity* _character;
	std::shared_ptr<Entity> _target;

public:
	Seek() = delete;
	Seek(Entity* character, std::shared_ptr<Entity> target)
		: _character(character)
		, _target(target)
	{ }
	SteeringOutput getSteering() const noexcept;
};

class Flee : public SteeringBehaviour
{
private:
	Entity* _character;
	std::shared_ptr<Entity> _target;

public:
	Flee() = delete;
	Flee(Entity* character, std::shared_ptr<Entity> target)
		: _character(character)
		, _target(target)
	{ }
	SteeringOutput getSteering() const noexcept;
};