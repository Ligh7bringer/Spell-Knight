#pragma once
#include <engine.h>

class TeleportComponent : public Component{
protected:
    std::weak_ptr<Entity> _player;
public:
    TeleportComponent() = delete;
    explicit TeleportComponent(Entity* p);

    void update(double dt) override;
    void render() override;
};