#include "scene_level1.h"
#include "../game.h"
#include <LevelSystem.h>
#include <thread>
#include "system_renderer.h"
#include <string>
#include "../../engine/lib_texture_manager/TextureManager.h"
#include "../entity_factory.h"
#include "../Log.h"
#include "../parallax_background.h"
#include "ecm.h"

using namespace std;
using namespace sf;

//Sprite background;	

static shared_ptr<Entity> player;

void Level1Scene::Load() {
  //setup view
  auto windowSize = Engine::getWindowSize();  
  _view.reset(FloatRect(0, 0, windowSize.x, windowSize.y));

  ls::loadLevelFile("res/lvl1.txt", 32.0f);
  //auto ho = Engine::getWindowSize().y - (ls::getHeight() * 32.f);
  //ls::setOffset(Vector2f(0, ho));

  // Create player
  player = EntityFactory::makePlayer(this, Vector2f(100.f, 100.f));
  _view.setCenter(player->getPosition());
  
  //initialise background and add layers
  _parBackground = ParallaxBackground(Vector2f(1280.f, 760.f));
  _parBackground.addLayer(0.5f, "forest.jpg");
  _parBackground.addLayer(0.8f, "trees.png");
  _parBackground.addLayer(1.2f, "ground.png");
  
  // Create some enemies  
  auto enemyPos = ls::findTiles(ls::baseTiles::ENEMY);

  for(int i = 0; i < enemyPos.size(); ++i)
  {
    auto p = ls::getTilePosition(enemyPos[i]);
    
    if(i == 0) {
      EntityFactory::makeSlime(this, p);	  		
    } else {
      EntityFactory::makeEyeDemon(this, p);
    }
  } 
  
  // Add physics colliders to level tiles.  
  EntityFactory::makeWalls(this);

  //create a power up  
  auto flamePos = ls::findTiles(ls::groundTiles::COIN);
  for(int i = 0; i < flamePos.size(); ++i) {
    auto fp = ls::getTilePosition(flamePos[i]);
    EntityFactory::makePowerUp(this, fp);
  }

  auto waterTiles = LevelSystem::findTiles(ls::baseTiles::DEADFALL);
  auto fishPos = ls::getTilePosition(waterTiles[0]);
  EntityFactory::makeFish(this, fishPos);

  //Simulate long loading times
  //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  LOG(INFO) << "Scene 1 loaded!";
  setLoaded(true);
}

void Level1Scene::Restart() {
  UnLoad();
  Load();
  LOG(INFO) << "Scene 1 Restarted!";
  //todo: optimised restart level
  /*
  //setup view
  //Vector2f windowSize = static_cast<Vector2f>(Engine::getWindowSize());
  //_view = View(FloatRect(0, 0, windowSize.x, windowSize.y));
  Renderer::resetView();


  ls::loadLevelFile("res/lvl1.txt", 32.0f);
  // reset player
  // delete player
  //player.reset();
  // remake player
  player = EntityFactory::makePlayer(this, Vector2f(100.f, 100.f));
  _view.setCenter(player->getPosition());

  // reset enemies
  auto enemyPos = ls::findTiles(ls::baseTiles::ENEMY);

  //if the enemies are no full health
  //else reset the pos
  //if(){}
  //or just delete them and make them again
  auto enemies = ents.find("enemy");
  for(auto enemy: enemies){
    ents.find("enemy").clear();
    enemy.reset();
  }
  for(int i = 0; i < enemyPos.size(); ++i)
  {
    auto p = ls::getTilePosition(enemyPos[i]);

    if(i == 0) {
      EntityFactory::makeSlime(this, p);
    } else {
      EntityFactory::makeEyeDemon(this, p);
    }
  }

  //create a power up
  //if there are no powerups
  //if(){}
  //or just delete and then remake
  auto flames = ents.find("flame");
  auto flamePos = ls::findTiles(ls::groundTiles::COIN);
  for(int i = 0; i < flamePos.size(); ++i) {
    auto fp = ls::getTilePosition(flamePos[i]);
    EntityFactory::makePowerUp(this, fp);
  }
   */
}

void Level1Scene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  //_view.reset();
  //Renderer::resetView();
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {  
  _parBackground.update(dt);

  if (ls::getTileAt(player->getPosition()) == ls::baseTiles::END) {
	  cout << "yeh won!!" << endl;
    Engine::ChangeScene((Scene*)&menu);
  }

  //move the view with the player
  if(player != nullptr) {
    float vx = player->getPosition().x;
    float vy = Engine::getWindowSize().y / 2.f;
    vx = floor(vx);
    vy = floor(vy);
    _view.setCenter(vx, vy);
    Renderer::setView(_view);
  }
  //Teleport to start if we fall off map.
  //restart level if we fall off map
  if (player->getPosition().y > ls::getHeight() * ls::getTileSize()) {
    LOG(DEBUG) << "no map left!!";
    //teleport(ls::getTilePosition(ls::findTiles(ls::baseTiles::START)[0]));
    Restart();
  }

  Scene::Update(dt);
}

void Level1Scene::Render() {
  _parBackground.render();

  ls::render(Engine::GetWindow());

  Scene::Render();
}


