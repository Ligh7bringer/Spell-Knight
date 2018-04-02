#ifndef GAMES_ENGINEERING_CMP_SPAWNER_H
#define GAMES_ENGINEERING_CMP_SPAWNER_H

#include "../../engine/lib_ecm/ecm.h"

class SpawnerComponent : public Component {
private:
    float _spawnTime;

public:
    SpawnerComponent() = delete;
    explicit SpawnerComponent(Entity* p);

    void update(double dt) override;
    void render() override {}
};


#endif //GAMES_ENGINEERING_CMP_SPAWNER_H
