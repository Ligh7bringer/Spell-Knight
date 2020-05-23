#include "cmp_state_machine.h"

using namespace std;

/*
* This component allows enemies to have different states and appear intelligent.
*/

StateMachineComponent::StateMachineComponent(Entity* p)
	: Component(p)
	, _currentState(nullptr)
{ }

//run current state's functionality
void StateMachineComponent::update(double dt)
{
	if(_currentState != nullptr)
	{
		_currentState->execute(_parent, dt);
	}
}

//adds a state to the state machine
void StateMachineComponent::addState(const string& name, shared_ptr<State> state) noexcept
{
	_states[name] = state;
}

//returns a state
shared_ptr<State> StateMachineComponent::getState(const string& name) const noexcept
{
	auto found = _states.find(name);
	if(found != _states.end())
	{
		return found->second;
	}

	return nullptr;
}

//removes a state
void StateMachineComponent::removeState(const string& name) noexcept { _states.erase(name); }

//changes the current state
void StateMachineComponent::changeState(const string& name) noexcept
{
	auto found = _states.find(name);
	if(found != _states.end())
	{
		_currentState = found->second;
		_currentStateName = found->first;
	}
}