#include "scene_level1.h"
#include "../game.h"
#include <LevelSystem.h>
#include <thread>
#include "system_renderer.h"
#include <string>
#include "../../engine/lib_texture_manager/TextureManager.h"
#include "../misc/entity_factory.h"
#include "../Log.h"
#include "../misc/parallax_background.h"
#include "ecm.h"

using namespace std;
using namespace sf;

//Sprite background;	

static shared_ptr<Entity> player;

void Level1Scene::Load() {
  //setup view
  auto windowSize = Engine::getWindowSize();  
  _view.reset(FloatRect(0, 0, windowSize.x, windowSize.y));

  ls::loadLevelFile("res/levels/lvl1.txt", 32.0f);
  //auto ho = Engine::getWindowSize().y - (ls::getHeight() * 32.f);
  //ls::setOffset(Vector2f(0, ho));
  
  //initialise background and add layers
  _parBackground = ParallaxBackground(Vector2f(windowSize.x, windowSize.y));
  _parBackground.addLayer(0.5f, "forest.jpg");
  _parBackground.addLayer(0.8f, "trees.png");
  _parBackground.addLayer(1.2f, "ground.png");
  
  Restart();

  LOG(INFO) << "Scene 1 loaded!";
  setLoaded(true);
}

void Level1Scene::Restart() {
  //remove all entities
  for(auto ent : ents.list) {
    ent->setForDelete();
  }

  ents.list.clear();

  // Create player
  player = EntityFactory::makePlayer(this, Vector2f(5500.f, 100.f));

  // Create some enemies  
  auto slimePos = LevelSystem::findTiles(LevelSystem::enemyTiles::SLIME);
  for(auto sp : slimePos) {
    auto p = LevelSystem::getTilePosition(sp);
    EntityFactory::makeSlime(this, p);
  }

  auto eyePos = LevelSystem::findTiles(LevelSystem::enemyTiles::EYE);
  for(auto ep : eyePos) {
    auto p = LevelSystem::getTilePosition(ep);
    EntityFactory::makeEyeDemon(this, p);
  }

  auto plantPos = LevelSystem::findTiles(LevelSystem::enemyTiles::PLANT);
  for(auto pp : plantPos) {
    auto p = LevelSystem::getTilePosition(pp);
    EntityFactory::makePlant(this, p);
  }
  
  // auto birdPos = LevelSystem::findTiles(LevelSystem::enemyTiles::BIRD);
  // for(auto bp : birdPos) {
  //   auto p = LevelSystem::getTilePosition(bp);
  //   EntityFactory::makeBird(this, p);
  // }
  
  // Add physics colliders to level tiles.  
  EntityFactory::makeWalls(this);

  //create a power up  
  auto flamePos = ls::findTiles(ls::groundTiles::COIN);
  for(int i = 0; i < flamePos.size(); ++i) {
    auto fp = ls::getTilePosition(flamePos[i]);
    EntityFactory::makePowerUp(this, fp);
  }

  //make fish
  auto waterTiles = LevelSystem::findTiles(ls::baseTiles::DEADFALL);
  auto fishPos = ls::getTilePosition(waterTiles[2]);
  EntityFactory::makeFish(this, fishPos);

  //get positions of moving tiles
  auto platformTile = LevelSystem::findTiles(ls::platformTiles::PLATFORM_MOVING);
  vector<Vector2f> positions;
  for (auto tile : platformTile) {
    auto pos = ls::getTilePosition(tile);
    positions.push_back(pos);
  }

  //create platforms
  for(int i = 0; i < platformTile.size(); i+= 2) {
    //for every two positions
    //the first one is the starting position
    auto start = ls::getTilePosition(platformTile[i]);
    //the second one is the destination position
    auto end = ls::getTilePosition(platformTile[i + 1]);
    //distance is end - start
    auto distance = end - start;
    EntityFactory::makeMovingPlatform(this, start, distance, 1.f);
  }

  //make falling platform
  platformTile = LevelSystem::findTiles(ls::platformTiles::PLATFORM_FALLING);
  auto platformPos = ls::getTilePosition(platformTile[0]);
  EntityFactory::makeFallingPlatform(this, platformPos);
  
  LOG(INFO) << "Scene 1 Restarted!";
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

  //move the view with the player
  if(player != nullptr) {
    float vx = player->getPosition().x;
    float vy = Engine::getWindowSize().y / 2.f;
    vx = floor(vx);
    vy = floor(vy);
    _view.setCenter(vx, vy);
    Renderer::setView(_view);
  }

  //restart level if we fall off map
  if (!player->isAlive()) {
    Restart();
  }

  Scene::Update(dt);
}

void Level1Scene::Render() {
  _parBackground.render();

  ls::render(Engine::GetWindow());

  Scene::Render();
}


