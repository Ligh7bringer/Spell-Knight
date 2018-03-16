#pragma once
#include <engine.h>

class PickUpComponent : public Component {
protected:
    std::weak_ptr<Entity> _player;

public:
    PickUpComponent() = delete;
    explicit PickUpComponent(Entity* p);

    void update(double dt) override;
    void render() override;


};