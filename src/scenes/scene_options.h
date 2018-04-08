#pragma once

#include "engine.h"
#include "../GUI/button.h"
#include "../GUI/menu.h"

class OptionsScene : public Scene {
private:
    Menu _optionsMenu;
    float _timer;

    void updateLabel(unsigned int id, double dt);

public:
    OptionsScene() = default;
    ~OptionsScene() override = default;

    void Load() override;
    void Render() override;

    void Update(const double& dt) override;
};
