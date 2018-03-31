#pragma once
#include "../../engine/lib_ecm/ecm.h"
#include "../GUI/panel.h"
#include <SFML/System/Clock.hpp>

class TimerComponent : public Component {
private:
    Panel _panel;
    sf::Clock _clock;

public:
    TimerComponent() = delete;
    explicit TimerComponent(Entity* p);

    void update(double dt) override;
    void render() override;
};