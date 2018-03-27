#include "steering.h"

using namespace sf;

SteeringOutput Seek::getSteering() const noexcept {
  SteeringOutput steering;
  steering.xdirection = _target->getPosition().x - _character->getPosition().x;
  //steering.xdirection = normalize(steering.xdirection);
  return steering;
}

SteeringOutput Flee::getSteering() const noexcept {
  SteeringOutput steering;
  steering.xdirection =  _character->getPosition().x - _target->getPosition().x;
  //steering.direction.x = normalize(steering.direction.x);
  return steering;
}