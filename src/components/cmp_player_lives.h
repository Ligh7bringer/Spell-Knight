#pragma once
#include "../../engine/lib_ecm/ecm.h"
#include "../GUI/panel.h"
//#include <SFML/Font.hpp>

class PlayerLivesComponent : public Component {
private:
    int _maxLives;
    int _lives;
    Panel _panel;

public:
    PlayerLivesComponent() = delete;
    explicit PlayerLivesComponent(Entity* p, int maxLives);

    void update(double dt) override;
    void render() override;

    void increaseLives(int num);
    void decreaseLives(int num);
    int getLives() const;
};