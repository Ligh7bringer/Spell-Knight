#pragma once
#include "../GUI/button.h"
#include "../GUI/panel.h"
#include "engine.h"

class GameOverScene : public Scene
{
private:
	Panel _panel;
	std::string _message;
	Button nextLevelbtn;
	Button restartLevelbtn;
	Button mainMenubtn;
	bool _init;
	float _timer;

public:
	GameOverScene() { }

	void Load() override;

	void Update(const double& dt) override;

	void Render() override;

	void UnLoad() override;

	void setText(const std::string& text);

	void nextLevel();

	//void Render() override;

	//GameOverScene() = default;
	//~GameOverScene() override = default;
};
