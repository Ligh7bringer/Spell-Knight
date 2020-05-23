#ifndef GAMES_ENGINEERING_SCENE_HIGHSCORE_H
#define GAMES_ENGINEERING_SCENE_HIGHSCORE_H

#include "../GUI/menu.h"
#include <engine.h>

class HighScoreScene : public Scene
{
public:
	HighScoreScene() = default;
	~HighScoreScene() override = default;

	void Load() override;

	void Update(const double& dt) override;

	void Render() override;

private:
	Menu _menu;
};

#endif //GAMES_ENGINEERING_SCENE_HIGHSCORE_H
