#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_player_animated_sprite.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_enemy_animated_sprite.h"
#include "../game.h"
#include <LevelSystem.h>
#include <thread>
#include "system_renderer.h"
#include <string>
#include <iostream>
#include "../../engine/lib_texture_manager/TextureManager.h"
#include "../components/cmp_ground_enemy_physics.h"
#include "../components/cmp_player_bullet.h"
#include "../components/cmp_enemy_turret.h"

using namespace std;
using namespace sf;

Texture tex;
//Sprite background;

static shared_ptr<Entity> player;

void Level1Scene::Load() {
  Vector2f windowSize = static_cast<Vector2f>(Engine::getWindowSize());

  cout << " Scene 1 Load" << endl;
  ls::loadLevelFile("res/lvl1.txt", 32.0f);
  //auto ho = Engine::getWindowSize().y - (ls::getHeight() * 32.f);
  //ls::setOffset(Vector2f(0, ho));

  tex = TextureManager::getTexture("forest.jpg");
  tex.setRepeated(true);
  _background.setTexture(tex);
  //set up repeated background
  auto pos = Vector2f(_background.getLocalBounds().width/2, _background.getLocalBounds().height/2);
  _background.setOrigin(pos);
  _background.setPosition(Vector2f(pos.x/4, pos.y));
  _background.setTextureRect(IntRect(0, 0, windowSize.x * 20, windowSize.y));  

  //setup view
  _view = View(FloatRect(0, 0, windowSize.x, windowSize.y));
  
  // Create player
  {
    player = makeEntity();
	  player->setPosition(Vector2f(100.f,100.f));
    player->addTag("player");
  
    player->addComponent<PlayerAnimatedSpriteComponent>(64, 64);
    player->addComponent<PlayerPhysicsComponent>(Vector2f(27.f, 62.f));
    player->addComponent<PlayerBulletComponent>();
  }


// Create some snakes
  {
	  for(int i = 0; i<ls::findTiles(ls::baseTiles::ENEMY).capacity();++i)
	  {
		  auto snakeEnemy = makeEntity();
 		  auto p = ls::getTilePosition(ls::findTiles(LevelSystem::baseTiles::ENEMY)[i]);
		  //check if normal ai snakes
		  
			  snakeEnemy->setPosition(p);
			  snakeEnemy->addComponent<EnemyAnimatedSpriteComponent>(64, 64);
			  // Add HurtComponent
			  snakeEnemy->addComponent<HurtComponent>();
			  snakeEnemy->addComponent<GroundEnemyPhysicsComponent>(Vector2f(35.f, 32.f));
			  // Add EnemyAIComponent
			  snakeEnemy->addComponent<EnemyAIComponent>();

			  /* add turret enemy
			  cout << "hey" << endl;
			  auto turretEnemy = makeEntity();
			  turretEnemy->setPosition(ls::getTilePosition(ls::findTiles('t')[0]));
			  auto t =turretEnemy->addComponent<EnemyAnimatedSpriteComponent>(64, 64);
			  t->setSpritesheet(TextureManager::getTexture("spritesheet_knight.png"));
			  t->setCurrentRow(0);
			  t->setNumberOfFrames(8);
			  t->setFrameTime(0.15f);
			  // Add HurtComponent
			  turretEnemy->addComponent<HurtComponent>();
			  turretEnemy->addComponent<GroundEnemyPhysicsComponent>(Vector2f(35.f, 32.f));
			  // Add EnemyAIComponent
			  turretEnemy->addComponent<EnemyTurretComponent>();
			  */
	  }
    
  }

  // Add physics colliders to level tiles.
  {
	auto walls = (ls::getGroundTiles());
    for (auto w : walls) {
		//cout << walls << endl;
      auto pos = ls::getTilePosition(w);
      pos += Vector2f(16.f, 16.f); //offset to center
      auto e = makeEntity();
      e->setPosition(pos);
      e->addComponent<PhysicsComponent>(false, Vector2f(32.f, 32.f));
    }
  }

  //Simulate long loading times
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  cout << " Scene 1 Load Done" << endl;

  setLoaded(true);
}

void Level1Scene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  //_view.reset();
  Renderer::resetView();
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {
  if (ls::getTileAt(player->getPosition()) == ls::baseTiles::END) {
	  cout << "yeh won!!" << endl;
    Engine::ChangeScene((Scene*)&level2);
  }

  if(player != nullptr) {
    _view.setCenter(player->getPosition().x, Engine::getWindowSize().y / 2.f);
    Renderer::setView(_view);
  }

  Scene::Update(dt);
}

void Level1Scene::Render() {
  //ensure background is drawn before anything else
  Engine::GetWindow().draw(_background);

  Scene::Render();

  ls::render(Engine::GetWindow());
}
