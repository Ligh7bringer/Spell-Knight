#include "scene_level1.h"
#include "../game.h"
#include <LevelSystem.h>
#include <thread>
#include "system_renderer.h"
#include <string>
#include <iostream>
#include "../../engine/lib_texture_manager/TextureManager.h"
#include "../entity_factory.h"
#include "../Log.h"

using namespace std;
using namespace sf;

//Sprite background;	

static shared_ptr<Entity> player;

void Level1Scene::Load() {

  //initialise background and add layers
  _parBackground = ParallaxBackground(Vector2f(1280.f, 760.f));
  _parBackground.addLayer(0.5f, "forest.jpg");
  _parBackground.addLayer(0.8f, "trees.png");
  _parBackground.addLayer(1.2f, "ground.png");

  //Vector2f windowSize = static_cast<Vector2f>(Engine::getWindowSize());

  cout << " Scene 1 Load" << endl;
  ls::loadLevelFile("res/lvl1_test.txt", 32.0f);
  //auto ho = Engine::getWindowSize().y - (ls::getHeight() * 32.f);
  //ls::setOffset(Vector2f(0, ho));

  //setup view
  _view = View(FloatRect(0, 0, Engine::getWindowSize().x, Engine::getWindowSize().y));
  //_view.zoom(0.7f);

  // Add physics colliders to level tiles.  
  EntityFactory::makeWalls(this);

  // Create player
  player = EntityFactory::makePlayer(this, Vector2f(100.f, 100.f));
  
  // Create some enemies  
  auto enemyPos = ls::findTiles(ls::baseTiles::ENEMY);

  for(int i = 0; i < enemyPos.size(); ++i)
  {
    auto p = ls::getTilePosition(enemyPos[i]);
    
    if(i < 1) {
      EntityFactory::makeSlime(this, p);	  		
    } else {
      EntityFactory::makeEyeDemon(this, p);
    }
  } 

  //create a powe up  
  auto flamePos = ls::findTiles(ls::groundTiles::COIN);
  for(int i = 0; i < flamePos.size(); ++i) {
    auto fp = ls::getTilePosition(flamePos[i]);
    EntityFactory::makePowerUp(this, fp);
  }

  //Simulate long loading times
  //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  LOG(INFO) << "Scene 1 loaded!";

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
  _parBackground.update(dt);

  if (ls::getTileAt(player->getPosition()) == ls::baseTiles::END) {
	  cout << "yeh won!!" << endl;
    Engine::ChangeScene((Scene*)&level2);
  }

  //move the view with the player
  if(player != nullptr) {
    _view.setCenter(player->getPosition().x, Engine::getWindowSize().y / 2.f);
    _parBackground.setTarget(_view.getCenter());

    Renderer::setView(_view);
  }

  Scene::Update(dt);
}

void Level1Scene::Render() {
  Scene::Render();

  ls::render(Engine::GetWindow());
}
