#include "scene_level1.h"
#include "../game.h"
#include <LevelSystem.h>
#include <thread>
#include "system_renderer.h"
#include <string>
#include <iostream>
#include "../../engine/lib_texture_manager/TextureManager.h"
#include "../entity_factory.h"

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

  //setup background
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

  auto flamePos = ls::findTiles(ls::groundTiles::COIN);
  for(int i = 0; i < flamePos.size(); ++i) {
    auto fp = ls::getTilePosition(flamePos[i]);
    EntityFactory::makePowerUp(this, fp);
  }

  //Simulate long loading times
  //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  cout << "Scene 1 Load Done" << endl;

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
  //if (ls::getTileAt(player->getPosition()) == ls::baseTiles::END) {
	  //cout << "yeh won!!" << endl;
   // Engine::ChangeScene((Scene*)&level2);
  //}

  //move the view with the player
  if(player != nullptr) {
    _view.setCenter(player->getPosition().x, Engine::getWindowSize().y / 2.f);
    Renderer::setView(_view);
  }

  Scene::Update(dt);
}

void Level1Scene::Render() {
  Scene::Render();

  ls::render(Engine::GetWindow());
}
