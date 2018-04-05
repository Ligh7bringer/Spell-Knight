#pragma once
#include <engine.h>

class PickUpComponent : public Component {
protected:
    std::weak_ptr<Entity> _player;
    unsigned int _points;

public:
    PickUpComponent() = delete;
    explicit PickUpComponent(Entity* p, unsigned int points);

    void update(double dt) override;
    void render() override;


};