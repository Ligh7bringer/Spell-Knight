#include <texture_manager.h>
#include "cmp_particles.h"
#include "../../engine/src/engine.h"

/*
* This component allows entities to emit particles.
*/

//create particle system
ParticleSystemComponent::ParticleSystemComponent(Entity* p, ParticleSystem::Type type) : Component(p),
                                                                                    _particles(type ,TextureManager::getTexture("particle.png"), 1.5f),
                                                                                    _type(type) {}

//update particle system and its position 
void ParticleSystemComponent::update(double dt) {
    _particles.setEmitter(_parent->getPosition());
    _particles.emitParticles(dt);
    _particles.update(dt);
}

//render particles
void ParticleSystemComponent::render() {
    Engine::GetWindow().draw(_particles);
}

//setter for colour of particles
void ParticleSystemComponent::setColour(sf::Color c) {
    //_particles.setParticleColor(c);
}