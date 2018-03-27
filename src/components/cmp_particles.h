#pragma once
#include "../../engine/lib_ecm/ecm.h"
#include "../misc/particle_system.h"

class ParticleSystemComponent : public Component {
private:
    ParticleSystem _particles;
public:
    ParticleSystemComponent() = delete;
    explicit ParticleSystemComponent(Entity* p);

    void update(double dt) override;
    void render();

    void setColour(sf::Color c);
};