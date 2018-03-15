#include "entity_factory.h"
#include "components/cmp_player_physics.h"
#include "components/cmp_player_animated_sprite.h"
#include "components/cmp_enemy_ai.h"
#include "components/cmp_hurt_player.h"
#include "components/cmp_enemy_animated_sprite.h"
#include "components/cmp_player_lives.h"
#include "components/cmp_player_bullet.h"
#include "components/cmp_enemy_physics.h"
#include "components/cmp_physics.h"
#include "../engine/lib_tile_level_loader/LevelSystem.h"

using namespace sf;

/*
* Factory class for easier creation of entities.
*/

//creates the player at position pos
std::shared_ptr<Entity> EntityFactory::makePlayer(Scene* scene, const Vector2f& pos) {
    auto player = scene->makeEntity();
    player->setPosition(pos);
    player->addTag("player");
  
    player->addComponent<PlayerAnimatedSpriteComponent>(64, 64);
    player->addComponent<PlayerPhysicsComponent>(Vector2f(27.f, 62.f));
    player->addComponent<PlayerBulletComponent>();
    player->addComponent<PlayerLivesComponent>(3);

    return player;
}

//creates a snake enemy at position pos
std::shared_ptr<Entity> EntityFactory::makeSnake(Scene* scene, const Vector2f& pos) {
    auto snakeEnemy = scene->makeEntity();
    snakeEnemy->addTag("enemy");
    // set position
    snakeEnemy->setPosition(pos);
    snakeEnemy->addComponent<EnemyAnimatedSpriteComponent>(64, 28);
    // Add HurtComponent
    snakeEnemy->addComponent<HurtComponent>();
    // Add EnemyAIComponent
    snakeEnemy->addComponent<EnemyAIComponent>();
    snakeEnemy->addComponent<EnemyPhysicsComponent>(Vector2f(64.f, 28.f), false);	
    //snakeEnemy->addComponent<PhysicsComponent>(false, Vector2f(64.f, 28.f));

    return snakeEnemy;
}

//creates the physics colliders for the tiles in the currently loaded level
void EntityFactory::makeWalls(Scene* scene) {
    auto walls = (ls::getGroundTiles());
    for (auto w : walls) {  
        auto pos = ls::getTilePosition(w);
        pos += Vector2f(16.f, 16.f); //offset to center
        
        auto e = scene->makeEntity();
        e->setPosition(pos);
        e->addComponent<PhysicsComponent>(false, Vector2f(32.f, 32.f));
  }
}