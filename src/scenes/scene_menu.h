#pragma once

#include "../GUI/menu.h"
#include "engine.h"

class MenuScene : public Scene
{
public:
	MenuScene() = default;
	~MenuScene() override = default;

	void Load() override;

	void Render() override;

	void Update(const double& dt) override;

private:
	Menu _mainMenu;
	float _delay;
};
