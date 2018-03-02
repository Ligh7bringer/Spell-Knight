#pragma once 
#include <ecm.h>

class HurtEnemyComponent : public Component {
protected:
    std::shared_ptr<Entity> _player;

public:
    void update(double dt) override;
    void render() override;

    explicit HurtEnemyComponent(Entity* p);
    HurtEnemyComponent() = delete;
};