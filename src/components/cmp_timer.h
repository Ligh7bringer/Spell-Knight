#pragma once
#include "../../engine/lib_ecm/ecm.h"
#include "../GUI/panel.h"
#include <SFML/System/Clock.hpp>

class TimerComponent : public Component {
private:
    Panel _panel;
    float _timer;

public:
    TimerComponent() = delete;
    explicit TimerComponent(Entity* p);

    void update(double dt) override;
    void render() override;

    int getTime() const;
};