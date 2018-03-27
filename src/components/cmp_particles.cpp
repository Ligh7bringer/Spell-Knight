#include "cmp_particles.h"
#include "../../engine/src/engine.h"

/*
* This component allows entities to emit particles.
*/

//create particle system
ParticleSystemComponent::ParticleSystemComponent(Entity* p) : Component(p), _particles(ParticleSystem(1000)) {
    //set colour of particles
    _particles.setParticleColor(sf::Color(0, 204, 204));                                            
}

//update particle system and its position 
void ParticleSystemComponent::update(double dt) {
    _particles.setEmitter(_parent->getPosition());
    _particles.update(dt);
}

//render particles
void ParticleSystemComponent::render() {
    Engine::GetWindow().draw(_particles);
}

//setter for colour of particles
void ParticleSystemComponent::setColour(sf::Color c) {
    _particles.setParticleColor(c);
}