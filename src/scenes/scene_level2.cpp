#include "scene_level2.h"
#include "../../engine/lib_audio_manager/audio_manager.h"
#include "../Log.h"
#include "../components/cmp_score.h"
#include "../components/cmp_timer.h"
#include "../config.h"
#include "../game.h"
#include "../misc/entity_factory.h"
#include "system_renderer.h"
#include <LevelSystem.h>
#include <engine.h>
#include <thread>
using namespace std;
using namespace sf;

//Sprite background;

static shared_ptr<Entity> player;
int score2;
int playerTime2;
Panel panel2;

void Level2Scene::Load()
{
	AudioManager::playMusic("background.wav", true);

	//setup view
	auto windowSize = Engine::getWindowSize();
	auto res = Engine::getResolution();
	if(res.x > 1366)
	{
		res.x = 1366;
		res.y = 768;
	}

	_view.reset(FloatRect(0, 0, res.x, res.y));

	ls::loadLevelFile("res/levels/lvl2.txt", 32.0f);
	//auto ho = Engine::getWindowSize().y - (ls::getHeight() * 32.f);
	//ls::setOffset(Vector2f(0, ho));

	//initialise background and add layers
	_parBackground = ParallaxBackground(Vector2f(res.x, res.y));
	_parBackground.addLayer(0.5f, "forest.jpg");
	_parBackground.addLayer(0.8f, "trees.png");
	_parBackground.addLayer(1.2f, "ground.png");

	Vector2f pos(windowSize.x / 2, windowSize.y / 2);
	panel2 = Panel(pos, Vector2f(300.f, 67.5f));
	panel2.setGUI(true);
	panel2.setPositionOfCentre(pos);
	panel2.setPanelColour(Color(102, 178, 255, 128));
	panel2.setTextSize(40);
	panel2.setText(Config::getLocalisedString("paused"));

	Restart();

	LOG(INFO) << "Scene 2 loaded!";
	setLoaded(true);
}

void Level2Scene::Restart()
{
	//remove all entities
	for(auto ent : ents.list)
	{
		ent->setForDelete();
	}

	ents.list.clear();

	// Create player
	player = EntityFactory::makePlayer(this, ls::getPosition(ls::baseTiles::START)[0]);

	// Create some enemies
	auto slimePos = LevelSystem::getPosition(LevelSystem::enemyTiles::SLIME);
	for(int i = 0; i < slimePos.size(); i += 2)
	{
		auto start = slimePos[i];
		auto end = slimePos[i + 1];
		auto distance = end - start;
		EntityFactory::makeSlime(this, start, distance, 1.5f);
	}

	auto eyePos = LevelSystem::getPosition(LevelSystem::enemyTiles::EYE);
	for(auto ep : eyePos)
	{
		EntityFactory::makeEyeDemon(this, ep);
	}

	auto cloudPos = LevelSystem::getPosition(LevelSystem::enemyTiles::BIRD);
	for(auto cp : cloudPos)
	{
		EntityFactory::makeCloud(this, cp);
	}
	auto plantPos = LevelSystem::getPosition(LevelSystem::enemyTiles::PLANT);
	for(auto pp : plantPos)
	{
		EntityFactory::makePlant(this, pp);
	}

	// Add physics colliders to level tiles.
	EntityFactory::makeWalls(this);

	//create collectibles
	auto coinPos = ls::getPosition(ls::groundTiles::COIN);
	for(auto cp : coinPos)
	{
		EntityFactory::makeCoin(this, cp);
	}
	auto potionPos = ls::getPosition(ls::groundTiles::POTION);
	for(auto pp : potionPos)
	{
		EntityFactory::makePotion(this, pp);
	}
	auto gemPos = ls::getPosition(ls::groundTiles::GEM);
	for(auto gp : gemPos)
	{
		EntityFactory::makeGem(this, gp);
	}

	auto portalPos = ls::getPosition(ls::baseTiles::END);
	EntityFactory::makePortal(this, portalPos[0]);

	//make fish
	auto waterTiles = LevelSystem::getPosition(ls::enemyTiles::FISH);
	auto fishPos = waterTiles[0];
	EntityFactory::makeFish(this, fishPos);

	//get positions of moving tiles
	auto platformTile = LevelSystem::getPosition(ls::platformTiles::PLATFORM_MOVING);
	//create platforms
	for(int i = 0; i < platformTile.size(); i += 2)
	{
		//for every two positions
		//the first one is the starting position
		auto start = platformTile[i];
		//the second one is the destination position
		auto end = platformTile[i + 1];
		//distance is end - start
		auto distance = end - start;
		EntityFactory::makeMovingPlatform(this, start, distance, 2.f);
	}

	//make falling platform
	platformTile = LevelSystem::getPosition(ls::platformTiles::PLATFORM_FALLING);
	for(int i = 0; i < platformTile.size(); ++i)
	{
		auto platformPos = platformTile[i];
		EntityFactory::makeFallingPlatform(this, platformPos);
	}
	//make heart
	auto heartPos = ls::getPosition(ls::groundTiles::HEART);
	for(auto hp : heartPos) EntityFactory::makeHeart(this, hp);

	//create boulder spawner
	//EntityFactory::makeSpawner(this, LevelSystem::getPosition(LevelSystem::enemyTiles::BOULDER)[0]);

	//create spikes
	auto spikePos = LevelSystem::getPosition(LevelSystem::enemyTiles::SPIKE);
	for(auto sp : spikePos) EntityFactory::makeSpike(this, sp);

	LOG(INFO) << "Scene 2 Restarted!";
}

void Level2Scene::UnLoad()
{
	LOG(INFO) << "Scene 2 Unload";
	AudioManager::stopMusic("background.wav");
	//don't forget to reset to default view or when the scene is changed or nothing is visible :D
	Renderer::resetView();
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void Level2Scene::Update(const double& dt)
{
	_parBackground.update(dt);

	//show game over scene if player dies
	if(!player->isAlive())
	{
		if(sf::length(player->getPosition() - ls::getPosition(ls::baseTiles::END)[0]) < 30.0f)
		{
			AudioManager::playSound("teleport.wav");
			gameOver.setText("Level Complete!!");
			auto scoreComp = player->get_components<PlayerScoreComponent>()[0];
			score2 = scoreComp->getPoints() * 2;
			gameOver.nextLevel();
		}
		else
		{
			AudioManager::playSound("death.wav");
			gameOver.setText("Game over!");
		}

		sf::sleep(sf::seconds(1.f));
		Engine::ChangeScene(&gameOver);
	}
	else
	{
		auto timeComp = player->get_components<TimerComponent>()[0];
		playerTime2 = timeComp->getTime();
		auto scoreComp = player->get_components<PlayerScoreComponent>()[0];
		score2 = scoreComp->getPoints();
	}

	//move the view with the player
	if(player != nullptr)
	{
		float vx = player->getPosition().x;
		float vy = Engine::getWindowSize().y / 2.f;
		vx = floor(vx);
		vy = floor(vy);
		_view.setCenter(vx, vy);
		Renderer::setView(_view);
	}

	Scene::Update(dt);
}

void Level2Scene::Render()
{
	_parBackground.render();

	ls::render(Engine::GetWindow());

	Scene::Render();
	if(Engine::isPaused())
	{
		panel2.render();
	}
}
