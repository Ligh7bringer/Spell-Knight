#pragma once
#include "ecm.h"

class Scene {
public:
    Scene() = default;

    virtual ~Scene() = default;
    virtual void Update(double dt);
    virtual void Render();
    virtual void Load() = 0;
    std::vector<std::shared_ptr<Entity>> getEnts() const;
protected:
    EntityManager _ents;
};