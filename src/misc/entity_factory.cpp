#include "entity_factory.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_animated_sprite.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_player_lives.h"
#include "../components/cmp_enemy_physics.h"
#include "../components/cmp_enemy_turret.h"
#include "../components/cmp_pickup.h"
#include "../components/cmp_score.h"
#include "../components/cmp_enemy_health.h"
#include "../components/cmp_state_machine.h"
#include "../components/cmp_ai_steering.h"
#include "../components/cmp_timer.h"
#include "../components/cmp_roaming.h"
#include "../components/cmp_spawner.h"
#include "../states/eye_states.h"
#include "../states/fish_states.h"
#include "../../engine/lib_tile_level_loader/LevelSystem.h"
#include "texture_manager.h"
#include "../states/bird_states.h"
#include "../components/cmp_teleport.h"
#include "../components/cmp_power_up.h"
#include "../components/cmp_particles.h"

using namespace sf;
using namespace std;

/*
* Factory class for easier creation of entities.
*/

//creates the player at position pos in Scene scene
std::shared_ptr<Entity> EntityFactory::makePlayer(Scene* scene, const Vector2f& pos) {
    auto player = scene->makeEntity();
    player->setPosition(pos);
    player->addTag("player");

    auto anim = player->addComponent<AnimatedSpriteComponent>(Vector2f(64.f, 64.f));
    anim->setSpritesheet(TextureManager::getTexture("wizard-1.png"));
    anim->setNumberOfFrames(4);
    //anim->setSpriteSheetPadding(2);
    anim->setFrameTime(0.2f);
    player->addComponent<PlayerPhysicsComponent>(Vector2f(27.f, 62.f));
    player->addComponent<PlayerAttackComponent>();
    player->addComponent<PlayerLivesComponent>(3);
    player->addComponent<PlayerScoreComponent>();
    player->addComponent<TimerComponent>(

    );

    return player;
}

//creates a snake enemy at position pos in Scene scene
std::shared_ptr<Entity> EntityFactory::makeSlime(Scene* scene, const Vector2f& pos, const Vector2f& distance, float time) {
    auto slime = scene->makeEntity();
    slime->addTag("enemy");
    // set position
    slime->setPosition(Vector2f(pos.x,pos.y+16.f));
    auto anim = slime->addComponent<AnimatedSpriteComponent>(Vector2f(32.f, 32.f));
    anim->setSpritesheet(TextureManager::getTexture("slime.png"));
    anim->setNumberOfFrames(4);
    // Add HurtComponent
    slime->addComponent<HurtComponent>();
    slime->addComponent<EnemyHealthComponent>(1);
    slime->addComponent<PhysicsComponent>(Vector2f(32.f, 32.f));
    //slime->addComponent<SteeringComponent>(scene->ents.find("player")[0]);
    slime->addComponent<RoamingComponent>(distance, time, false);

    return slime;
}

std::shared_ptr<Entity> EntityFactory::makeFish(Scene* scene, const Vector2f& pos) {
    auto fish = scene->makeEntity();
    fish->addTag("enemy");
    // set position
    fish->setPosition(pos);
    auto anim = fish->addComponent<AnimatedSpriteComponent>(Vector2f(50.f, 32.f));
    anim->setSpritesheet(TextureManager::getTexture("sheet_fish.png"));
    anim->setNumberOfFrames(5);
    // Add HurtComponent
    fish->addComponent<HurtComponent>();
    fish->addComponent<EnemyHealthComponent>(1);
    auto physics = fish->addComponent<EnemyPhysicsComponent>(true, Vector2f(32.f, 32.f));
    physics->setMass(2.f);
    physics->setGravityScale(0);
    auto sm = fish->addComponent<StateMachineComponent>();
    sm->addState("jumping", make_shared<JumpingState>());
    sm->addState("swimming", make_shared<SwimmingState>(scene->ents.find("player")[0]));
    sm->changeState("swimming");

    return fish;
}

//creates an eye demon enemy at position pos in Scene scene
std::shared_ptr<Entity> EntityFactory::makeEyeDemon(Scene* scene, const sf::Vector2f& pos) {
    auto eyeDemon = scene->makeEntity();
    eyeDemon->addTag("enemy");
    eyeDemon->setPosition(pos);
    auto anim = eyeDemon->addComponent<AnimatedSpriteComponent>(Vector2f(50.f, 50.f));
    anim->setSpritesheet(TextureManager::getTexture("eyesleep.png"));
    anim->setNumberOfFrames(4);
    eyeDemon->addComponent<HurtComponent>();
    eyeDemon->addComponent<EnemyHealthComponent>(1);
    eyeDemon->addComponent<EnemyPhysicsComponent>(true, sf::Vector2f(50.f, 50.f));
    auto sm = eyeDemon->addComponent<StateMachineComponent>();
    sm->addState("sleeping", std::make_shared<SleepingState>(scene->ents.find("player")[0], "flying"));
    sm->addState("flying", std::make_shared<FlyingState>());
    sm->changeState("sleeping");

    return eyeDemon;
}

//makes a plant "turret"
std::shared_ptr<Entity> EntityFactory::makePlant(Scene* scene, const sf::Vector2f& pos) {
    auto plant = scene->makeEntity();
    plant->addTag("enemy");
    plant->setPosition(pos);

    auto anim = plant->addComponent<AnimatedSpriteComponent>(Vector2f(64.f, 34.f));
    anim->setSpritesheet(TextureManager::getTexture("plant-attack.png"));
    anim->setNumberOfFrames(4);
    anim->setFacingRight(false);

    auto physics = plant->addComponent<EnemyPhysicsComponent>(true, anim->getSize());
    physics->setRestitution(0.f);
    physics->setFriction(20.f);

    auto bullet = plant->addComponent<EnemyTurretComponent>();
    bullet->setDirection(Vector2f(-7.f,8.f));
    bullet->setOffset(-anim->getSize());

    plant->addComponent<EnemyHealthComponent>(1);
    plant->addComponent<HurtComponent>();

    return plant;
}

std::shared_ptr<Entity> EntityFactory::makeCloud(Scene *scene, const sf::Vector2f &pos) {
    auto cloud = scene->makeEntity();
    cloud->addTag("enemy");
    cloud->setPosition(pos);

    auto anim = cloud->addComponent<AnimatedSpriteComponent>(Vector2f(64.f,160.f));
    anim->setSpritesheet(TextureManager::getTexture("lightning_1.png"));
    anim->setNumberOfFrames(1);
    anim->setFrameTime(0.1f);

    auto physics = cloud->addComponent<EnemyPhysicsComponent>(true, Vector2f(50.f, 50.f));
    physics->setGravityScale(0);
    physics->setRestitution(0.f);
    physics->setFriction(20.f);

    auto bullet = cloud->addComponent<EnemyTurretComponent>();
    bullet->setDirection(Vector2f(0.f, 1.f));
    bullet->setOffset(Vector2f(34.f, 51.f));

    cloud->addComponent<HurtComponent>();
    cloud->addComponent<EnemyHealthComponent>(1);
    cloud->addComponent<SteeringComponent>(scene->ents.find("player")[0]);

    auto sm = cloud->addComponent<StateMachineComponent>();
    sm->addState("sleeping", std::make_shared<SleepingState>(scene->ents.find("player")[0], "flying"));
    sm->addState("flying", std::make_shared<FlyingbirdState>(scene->ents.find("player")[0]));
    sm->changeState("sleeping");

    return cloud;
}

//makes a collectible in Scene scene at position pos
std::shared_ptr<Entity> EntityFactory::makePotion(Scene *scene, const sf::Vector2f &pos) {
    auto potion = scene->makeEntity();
    potion->setPosition(pos);
    auto pl = scene->ents.find("player")[0];
    auto attack = pl->get_components<PlayerAttackComponent>()[0];
    //use a random potion to change the players attack
    auto row = rand() % 4;

    auto pu = potion->addComponent<PowerUpComponent>(10, attack->getAttack(row).type);
    pu->giveHealth(10);

    auto anim = potion->addComponent<AnimatedSpriteComponent>(Vector2f(32.f, 32.f));
    anim->setSpritesheet(TextureManager::getTexture("potions.png"));
    anim->setCurrentRow(row);

    return potion;
}


std::shared_ptr<Entity> EntityFactory::makeGem(Scene *scene, const sf::Vector2f &pos) {
    auto gem = scene->makeEntity();
    gem->setPosition(pos);

    gem->addComponent<PickUpComponent>(30);

    auto anim = gem->addComponent<AnimatedSpriteComponent>(Vector2f(32.f, 32.f));
    anim->setSpritesheet(TextureManager::getTexture("gems.png"));
    anim->setNumberOfFrames(6);
    anim->setCurrentRow(rand() % 2);
    anim->setFrameTime(0.1f);

    return gem;
}

std::shared_ptr<Entity> EntityFactory::makeCoin(Scene *scene, const sf::Vector2f &pos) {
    auto coin = scene->makeEntity();
    coin->setPosition(pos);

    coin->addComponent<PickUpComponent>(20);

    auto anim = coin->addComponent<AnimatedSpriteComponent>(Vector2f(32.f, 32.f));
    anim->setSpritesheet(TextureManager::getTexture("coin.png"));
    anim->setNumberOfFrames(9);
    anim->setFrameTime(0.1f);

    return coin;
}

//makes a portal to the end of the level scene
std::shared_ptr<Entity> EntityFactory::makePortal(Scene* scene, const sf::Vector2f &pos) {
    auto p = scene->makeEntity();
  p->addTag("portal");
  p->setPosition(pos);
  p->addComponent<TeleportComponent>();

  auto anim = p->addComponent<AnimatedSpriteComponent>(Vector2f(32.f,72.f));
  anim->setSpritesheet(TextureManager::getTexture("portal.png"));
  anim->setNumberOfFrames(3);
  anim->setFrameTime(0.2f);

  return p;
}

std::shared_ptr<Entity> EntityFactory::makeMovingPlatform(Scene* scene, const sf::Vector2f& pos, const sf::Vector2f& distance, float time) {
    auto platform = scene->makeEntity();
    platform->setPosition(pos);
    auto anim = platform->addComponent<AnimatedSpriteComponent>(Vector2f(64.f, 32.f));
    anim->setSpritesheet(TextureManager::getTexture("platform.png"));
    //use a kinematic body
    auto physics = platform->addComponent<PhysicsComponent>(anim->getSize());
    physics->setRestitution(0);
    physics->setGravityScale(0);
    physics->setFriction(1.f);
    auto moving = platform->addComponent<RoamingComponent>(distance, time, true);

    return platform;
}

std::shared_ptr<Entity> EntityFactory::makeFallingPlatform(Scene* scene, const sf::Vector2f& pos) {
    auto platform = scene->makeEntity();
    platform->setPosition(pos);
    auto anim = platform->addComponent<AnimatedSpriteComponent>(Vector2f(64.f, 32.f));
    anim->setSpritesheet(TextureManager::getTexture("platform.png"));
    //use a kinematic body
    auto physics = platform->addComponent<PhysicsComponent>(true, anim->getSize());
    physics->setGravityScale(0);
    physics->setRestitution(0);

    return platform;
}

std::shared_ptr<Entity> EntityFactory::makeSpawner(Scene *scene, const sf::Vector2f &pos) {
    auto spawner = scene->makeEntity();
    spawner->setPosition(pos);
    spawner->addComponent<SpawnerComponent>();

    return spawner;
}

std::shared_ptr<Entity> EntityFactory::makeSpike(Scene *scene, const sf::Vector2f &pos) {
    auto spike = scene->makeEntity();
    spike->setPosition(pos);

    auto anim = spike->addComponent<AnimatedSpriteComponent>(Vector2f(32.f, 64.f));
    anim->setSpritesheet(TextureManager::getTexture("spike.png"));

    auto size = anim->getSize();
    auto physics = spike->addComponent<PhysicsComponent>(false, Vector2f(size.x / 2.f, size.y));

    spike->addComponent<HurtComponent>();

    return spike;
}

//creates the physics colliders for the tiles in the currently loaded level in Scene scene
void EntityFactory::makeWalls(Scene* scene) {
  auto walls = (ls::getGroundTiles());
  for (auto w: walls) {
    auto pos = ls::getTilePosition(w);
    pos += Vector2f(16.f, 16.f);
    auto e = scene->makeEntity();
    e->setPosition(pos);
    e->addComponent<PhysicsComponent>(false, Vector2f(32.f, 32.f));
  }


}
