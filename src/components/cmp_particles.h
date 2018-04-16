#pragma once
#include "../../engine/lib_ecm/ecm.h"
#include "../misc/particle_system.h"

class ParticleSystemComponent : public Component {
private:
    ParticleSystem _particles;
    ParticleSystem::Type _type;
    bool _repeat;
    float _timer;

public:
    ParticleSystemComponent() = delete;
    explicit ParticleSystemComponent(Entity* p, ParticleSystem::Type type,  const std::string& tex);

    void update(double dt) override;
    void render() override;

    void setColour(sf::Color c);
    void setRepeat(bool r);
    void setEmissionRate(float rate);
    void setEmitterSize(const sf::Vector2f& size);
    void setOffset(const sf::Vector2f& offset);
    void setLifetime(float lt);
};