#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_player_animated_sprite.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_enemy_animated_sprite.h"
#include "../components/cmp_hurt_enemy.h"
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
#include "../components/cmp_enemy_physics.h"

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

  tex = TextureManager::getTexture("game_background_4.png");
  tex.setRepeated(true);
  _background.setTexture(tex);
  //set up repeated background
  auto pos = Vector2f(_background.getLocalBounds().width/2, _background.getLocalBounds().height/2);
  _background.setOrigin(pos);
  _background.setPosition(Vector2f(pos.x/4, pos.y));
  _background.setTextureRect(IntRect(0, 0, windowSize.x * 20, windowSize.y));  

  //setup view
  _view = View(FloatRect(0, 0, windowSize.x, windowSize.y));
  _view.zoom(0.7f);
  
  // Create player
  {
    player = makeEntity();
	  player->setPosition(Vector2f(100.f,100.f));
    player->addTag("player");
  
    player->addComponent<PlayerAnimatedSpriteComponent>(64, 64);
    player->addComponent<PlayerPhysicsComponent>(Vector2f(27.f, 62.f));
    player->addComponent<PlayerBulletComponent>();
  }


// Create some enemies
  {
    auto enemyPos = ls::findTiles(ls::baseTiles::ENEMY);
	  for(int i = 0; i < enemyPos.size(); ++i)
	  {
		  auto snakeEnemy = makeEntity();
      snakeEnemy->addTag("enemy");
 		  auto p = ls::getTilePosition(enemyPos[i]);
		  //check if normal ai snakes
		  if (i<3)
		  {
			 snakeEnemy->setPosition(p);
			  snakeEnemy->addComponent<EnemyAnimatedSpriteComponent>(64, 28);
			  // Add HurtComponent
			  snakeEnemy->addComponent<HurtComponent>();
			  // Add EnemyAIComponent
			 snakeEnemy->addComponent<EnemyAIComponent>();
			 snakeEnemy->addComponent<EnemyPhysicsComponent>(Vector2f(64.f, 28.f), false);
		  }
		  else 
		  {
			  auto eyeEnemy = makeEntity();
        eyeEnemy->addTag("enemy");
			  eyeEnemy->setPosition(Vector2f(p.x+i*500.f, p.y));
			  auto t = eyeEnemy->addComponent<AnimatedSpriteComponent>(64,37);
			  t->setSpritesheet(TextureManager::getTexture("sheet_eye_flyer.png"));
			  t->setCurrentRow(0);
			  t->setNumberOfFrames(5);
			  t->setFrameTime(0.15f);
			  // Add HurtComponent
			  eyeEnemy->addComponent<HurtComponent>();
			  // Add EnemyAIComponent
			  eyeEnemy->addComponent<EnemyAIComponent>();
			  eyeEnemy->addComponent<EnemyPhysicsComponent>(Vector2f(64.f, 37.f), true);
		  }
		  // else 
		  // {
			//   auto eyeEnemy = makeEntity();
      //   eyeEnemy->addTag("enemy");
			//   eyeEnemy->setPosition(Vector2f(p.x+i*500.f, p.y));
			//   auto t = eyeEnemy->addComponent<AnimatedSpriteComponent>(64, 64);
			//   t->setSpritesheet(TextureManager::getTexture("sheet_eye_flyer.png"));
			//   t->setCurrentRow(0);
			//   t->setNumberOfFrames(5);
			//   t->setFrameTime(0.15f);
			//   // Add HurtComponent
			//   eyeEnemy->addComponent<HurtComponent>();
			//   // Add EnemyAIComponent
			//   eyeEnemy->addComponent<EnemyAIComponent>();
			//   eyeEnemy->addComponent<AirEnemyPhysicsComponent>(Vector2f(64.f, 64.f));
			//   //eyeEnemy->addComponent<HurtEnemyComponent>();
		  // }
		  //else {
			  //add turret enemy
			  /*cout << "adding turret enemy" << endl;
			  auto turretEnemy = makeEntity();
			  turretEnemy->setPosition(ls::getTilePosition(ls::findTiles('t')[0]));
			  auto t = turretEnemy->addComponent<EnemyAnimatedSpriteComponent>(64, 64);
			  t->setSpritesheet(TextureManager::getTexture("sheet_snake_walk.png"));
			  t->setNumberOfFrames(5);
			  t->setFrameTime(0.15f);
			  // Add HurtComponent
			  turretEnemy->addComponent<HurtComponent>();
			  turretEnemy->addComponent<GroundEnemyPhysicsComponent>(Vector2f(35.f, 32.f));
			  // Add EnemyAIComponent
			  turretEnemy->addComponent<EnemyTurretComponent>();*/
		 // }
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
