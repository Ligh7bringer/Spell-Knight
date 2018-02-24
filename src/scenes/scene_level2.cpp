#include "scene_level2.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_enemy_turret.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
void Level2Scene::Load() {
  cout << "Scene 2 Load" << endl;
  ls::loadLevelFile("res/level_2.txt", 32.0f);
  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, 0.f));

  // Create player
  {
    // *********************************
    player = makeEntity();
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
    auto s = player->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
    s->getShape().setFillColor(Color::Magenta);
    s->getShape().setOrigin(10.f, 15.f);
    // *********************************
    player->addTag("player");
    player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
  }

  // Create Enemy
  {
    auto enemy = makeEntity();
    enemy->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[0]) +
                       Vector2f(0, 24));
    // *********************************
    // Add HurtComponent
    enemy->addComponent<HurtComponent>();
    // Add ShapeComponent, Red 16.f Circle
    auto s = enemy->addComponent<ShapeComponent>();
    s->setShape<CircleShape>(16.f, 16.f);
    s->getShape().setFillColor(Color::Red);
    s->getShape().setOrigin(Vector2f(16.f, 16.f));
    // Add EnemyAIComponent
    enemy->addComponent<EnemyAIComponent>();
    // *********************************
  }

  // Create Turret
  {
    auto turret = makeEntity();
    turret->setPosition(ls::getTilePosition(ls::findTiles('t')[0]) +
                        Vector2f(16.f, 0));
    auto s = turret->addComponent<ShapeComponent>();
    s->setShape<sf::CircleShape>(16.f, 3);
    s->getShape().setFillColor(Color::Red);
    s->getShape().setOrigin(16.f, 16.f);
    turret->addComponent<EnemyTurretComponent>();
  }

  // Add physics colliders to level tiles.
  {
    // *********************************
    auto walls = ls::findTiles(ls::WALL);
    for(auto w : walls) {
      auto pos = ls::getTilePosition(w);
      pos += Vector2f(16.f, 16.f);
      auto e = makeEntity();
      e->setPosition(pos);
      e->addComponent<PhysicsComponent>(false, Vector2f(32.f, 32.f));
    }
   // *********************************
  }

  cout << " Scene 2 Load Done" << endl;
  setLoaded(true);
}

void Level2Scene::UnLoad() {
  cout << "Scene 2 UnLoad" << endl;
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Level2Scene::Update(const double& dt) {
  Scene::Update(dt);
  const auto pp = player->getPosition();
  if (ls::getTileAt(pp) == ls::END) {
    Engine::ChangeScene((Scene*)&level3);
  } else if (!player->isAlive()) {
    Engine::ChangeScene((Scene*)&level2);
  }
}

void Level2Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
