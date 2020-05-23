#include "scene_highscore.h"
#include "../config.h"
#include "../game.h"

void HighScoreScene::Load()
{
	resetView();

	_menu = Menu();
	_menu.setPosition(sf::Vector2f(500.f, 200.f));
	_menu.addTitle(Config::getLocalisedString("hiscore"));

	for(auto& s : Config::getScore(""))
	{
		_menu.addButton(s);
	}

	_menu.addButton(Config::getLocalisedString("main_menu"));

	setLoaded(true);
}

void HighScoreScene::Update(const double& dt)
{
	_menu.update(dt);
	if(_menu.getMenuResponse() == 3)
	{
		Engine::ChangeScene((Scene*)&menu);
	}

	Scene::Update(dt);
}

void HighScoreScene::Render()
{
	_menu.render();
	Scene::Render();
}
