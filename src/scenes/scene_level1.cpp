#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_animated_sprite.h"
#include "../components/cmp_player_animated_sprite.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include "system_renderer.h"
#include <string>

using namespace std;
using namespace sf;

Texture tex;
Sprite background;

static shared_ptr<Entity> player;

void Level1Scene::Load() {
  cout << " Scene 1 Load" << endl;
<<<<<<< HEAD
  ls::loadLevelFile("res/level_1.txt", 32.0f);
  //auto ho = Engine::getWindowSize().y - (ls::getHeight() * 32.f);
  //ls::setOffset(Vector2f(0, ho));
=======
  ls::loadLevelFile("res/level_2.txt", 32.0f);
>>>>>>> 4e71b5041ccbbcc56d807e1f9d6aa04c520548dd

  //setup background
  if(!tex.loadFromFile("res/img/tiles/forest.jpg")) {
    cout << "Couldn't load forest.jpg" << endl;
  }

  _background.setTexture(tex);

  //setup view
  Vector2f windowSize = static_cast<Vector2f>(Engine::getWindowSize());
  _view = View(FloatRect(0, 0, windowSize.x, windowSize.y));

  // Create player
  {
    player = makeEntity();
<<<<<<< HEAD
	player->setPosition(Vector2f(100.f,100.f));
    auto s = player->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
    s->getShape().setFillColor(Color::Magenta);
    s->getShape().setOrigin(10.f, 15.f);
=======
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
    player->addComponent<PlayerAnimatedSpriteComponent>();
>>>>>>> 4e71b5041ccbbcc56d807e1f9d6aa04c520548dd

    player->addComponent<PlayerPhysicsComponent>(Vector2f(32.f, 64.f));
  }

  // Add physics colliders to level tiles.
  {
	auto walls = (ls::getGroundTiles());
    for (auto w : walls) {
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
    Engine::ChangeScene((Scene*)&menu);
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
