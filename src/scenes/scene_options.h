#pragma once

#include "engine.h"
#include "../GUI/button.h"

class OptionsScene : public Scene {
public:
    OptionsScene() = default;
    ~OptionsScene() override = default;

    void Load() override;
    void Render() override;

    void Update(const double& dt) override;
};
