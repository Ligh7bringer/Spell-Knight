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
    explicit PlayerLivesComponent(Entity* p, unsigned int lives);

    void update(double dt) override;
    void render() override;

    void increaseLives(unsigned int num);
    void decreaseLives(unsigned int num);
    int getLives() const;
};