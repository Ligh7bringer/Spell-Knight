#pragma once

#include "engine.h"
#include "../GUI/button.h"
#include "../GUI/menu.h"

class OptionsScene : public Scene {
private:
    Menu _optionsMenu;
    unsigned int _id;
    bool _flag;
    float _delay;

    std::map<std::string, sf::Vector2u> _resolutionData;
    std::map<int, std::string> _actionData;
    std::map<std::string, std::string> _langData;

    void initResolutions();
    void initActions();
    void initLang();
    void updateButton(unsigned int id);

public:
    OptionsScene() = default;
    ~OptionsScene() override = default;

    void Load() override;
    void Render() override;

    void Update(const double& dt) override;
};
