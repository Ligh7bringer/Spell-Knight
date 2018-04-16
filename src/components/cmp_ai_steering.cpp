#include "cmp_ai_steering.h"
#include "LevelSystem.h"
#include "../components/cmp_enemy_physics.h"

using namespace sf;


void SteeringComponent::update(double dt) {
  //if target (player) is more than 100 pixels away seek
  if(length(_parent->getPosition() - _player->getPosition()) > 100.f){
    _output = _seek.getSteering();
  }
  //if target player is less than 50 pixels away flee
  else if(_parent->getPosition().x - _player->getPosition().x < 50.f){
    _output =_flee.getSteering();
  }
}

SteeringComponent::SteeringComponent(Entity* p, std::shared_ptr<Entity> player) : _player(player), _seek(Seek(p, player)),
          _flee(Flee(p, player)), Component(p) {}

SteeringOutput SteeringComponent::getOutput() {
  return _output;
}
