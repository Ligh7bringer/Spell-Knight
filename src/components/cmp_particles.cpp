#include <texture_manager.h>
#include "cmp_particles.h"
#include "../../engine/src/engine.h"

/*
* This component allows entities to emit particles.
*/

//create particle system
ParticleSystemComponent::ParticleSystemComponent(Entity* p, ParticleSystem::Type type, const std::string& tex) : Component(p),
                                                                                         _particles(type , TextureManager::getTexture(tex), 1.5f),
                                                                                         _type(type), _repeat(true), _timer(2.0f) {}

//update particle system and its position
void ParticleSystemComponent::update(double dt) {
    if(_repeat) {
        _particles.setEmitter(_parent->getPosition());
        _particles.update(dt);
        _particles.emitParticles(dt);
    } else {
        _timer -= dt;
        _particles.setEmitter(_parent->getPosition());
        _particles.update(dt);
        if(_timer > 0.0f) {
            _particles.emitParticles(dt);
        }
    }
}

//render particles
void ParticleSystemComponent::render() {
    Engine::GetWindow().draw(_particles);
}

//setter for colour of particles
void ParticleSystemComponent::setColour(sf::Color c) {
    _particles.setColour(c);
}

void ParticleSystemComponent::setRepeat(bool r) {
    _repeat = r;
}

void ParticleSystemComponent::setEmissionRate(float rate) {
    _particles.setEmissionRate(rate);
}

void ParticleSystemComponent::setEmitterSize(const sf::Vector2f &size) {
    _particles.setEmitterSize(size);
}

void ParticleSystemComponent::setOffset(const sf::Vector2f &offset) {
    _particles.setEmitOffset(offset);
}

void ParticleSystemComponent::setLifetime(float lt) {
    _particles.setLifetime(lt);
}
