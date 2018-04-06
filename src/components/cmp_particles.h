#pragma once
#include "../../engine/lib_ecm/ecm.h"
#include "../misc/particle_system.h"

class ParticleSystemComponent : public Component {
private:
    ParticleSystem _particles;
    ParticleSystem::Type _type;
public:
    ParticleSystemComponent() = delete;
    explicit ParticleSystemComponent(Entity* p, ParticleSystem::Type type);

    void update(double dt) override;
    void render();

    void setColour(sf::Color c);
};