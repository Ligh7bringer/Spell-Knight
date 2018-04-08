#pragma once

#include "engine.h"
#include "../GUI/menu.h"

class MenuScene : public Scene {
public:
    MenuScene() = default;
    ~MenuScene() override = default;

    void Load() override;
    void Render() override;

    void Update(const double& dt) override;

private:
    Menu _mainMenu;
};
