#pragma once
#include <engine.h>

class PickUpComponent : public Component {
protected:
    std::weak_ptr<Entity> _player;
    unsigned int _points;
    bool _givesHealth;
    unsigned int _health;

public:
    PickUpComponent() = delete;
    explicit PickUpComponent(Entity* p, unsigned int points);

    void update(double dt) override;
    void render() override;

    void giveHealth(unsigned int health);
};