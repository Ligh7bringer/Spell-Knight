#pragma once
#include <ecm.h>
#include "../steering.h"

class SteeringComponent : public Component{
protected:
    Seek _seek;
    Flee _flee;
    std::shared_ptr<Entity> _player;
    SteeringOutput _output;
public:
    void update(double) override;
    void render() override {}
    explicit SteeringComponent(Entity *p, std::shared_ptr<Entity> player);
    SteeringComponent() = delete;
    SteeringOutput getOutput();
};