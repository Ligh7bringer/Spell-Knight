#pragma once
#include "../components/cmp_state_machine.h"

class SwimmingState : public State
{
private:
	sf::Vector2f _direction;
	std::shared_ptr<Entity> _player;

public:
	SwimmingState() = delete;
	explicit SwimmingState(std::shared_ptr<Entity>& player)
		: _player(player)
		, _direction(1.f, 0)
	{ }

	void execute(Entity*, double) noexcept override;
};

class JumpingState : public State
{
private:
	sf::Vector2f _direction;

public:
	JumpingState()
		: _direction(sf::Vector2f(1.0f, 1.f))
	{ }

	void execute(Entity*, double) noexcept override;
};
