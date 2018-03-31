#pragma once
#include "engine.h"
#include "../GUI/panel.h"

class GameOverScene : public Scene {
private:
    Panel _panel;
    std::string _message;
    int _score;
    int _time;

public:
    void Load() override;

    void Update(const double& dt) override;

    void Render() override;

    void UnLoad() override;

    void setText(const std::string& text);

    //void Render() override;

    //GameOverScene() = default;
    //~GameOverScene() override = default;
};
