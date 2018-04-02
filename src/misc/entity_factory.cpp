#include "entity_factory.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_animated_sprite.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_player_lives.h"
#include "../components/cmp_player_attack.h"
#include "../components/cmp_enemy_physics.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_enemy_turret.h"
#include "../components/cmp_pickup.h"
#include "../components/cmp_score.h"
#include "../components/cmp_enemy_health.h"
#include "../components/cmp_state_machine.h"
#include "../components/cmp_ai_steering.h"
#include "../components/cmp_timer.h"
#include "../components/cmp_roaming.h"
#include "../components/cmp_spawner.h"
#include "../states/slime_states.h"
#include "../states/eye_states.h"
#include "../states/fish_states.h"
#include "../../engine/lib_tile_level_loader/LevelSystem.h"
#include "texture_manager.h"
#include "../states/bird_states.h"

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
    player->addComponent<TimerComponent>();

    return player;
}

//creates a snake enemy at position pos in Scene scene
std::shared_ptr<Entity> EntityFactory::makeSlime(Scene* scene, const Vector2f& pos, const Vector2f& distance, float time) {
    auto slime = scene->makeEntity();
    slime->addTag("enemy");
    // set position
    slime->setPosition(pos);
    auto anim = slime->addComponent<AnimatedSpriteComponent>(Vector2f(32.f, 32.f));
    anim->setSpritesheet(TextureManager::getTexture("slime.png"));
    anim->setNumberOfFrames(4);
    // Add HurtComponent
    slime->addComponent<HurtComponent>();
    slime->addComponent<EnemyHealthComponent>(1);
    slime->addComponent<EnemyPhysicsComponent>(true, Vector2f(32.f, 32.f));
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
std::shared_ptr<Entity> EntityFactory::makePowerUp(Scene* scene, const sf::Vector2f& pos) {
    auto pu = scene->makeEntity();
    pu->addTag("flame");
    pu->setPosition(pos);
    pu->addComponent<PickUpComponent>();

    auto anim = pu->addComponent<AnimatedSpriteComponent>(Vector2f(32.f, 32.f));
    anim->setSpritesheet(TextureManager::getTexture("flame.png"));
    anim->setNumberOfFrames(4);
    anim->setFrameTime(0.1f);

    return pu;
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

//creates the physics colliders for the tiles in the currently loaded level in Scene scene
void EntityFactory::makeWalls(Scene* scene) {
    auto walls = (ls::getGroundTiles());
    for(auto w: walls){
        auto pos = ls::getTilePosition(w);
        pos += Vector2f(16.f,16.f);
        auto e = scene->makeEntity();
        e->setPosition(pos);
        e->addComponent<PhysicsComponent>(false, Vector2f(32.f, 32.f));
    }

/*
    auto walls = (ls::getGroundTiles());
    struct tp {
        sf::Vector2f p;
        sf::Vector2f s;
    };
    std::vector<tp> tps;
    const auto tls = Vector2f(ls::getTileSize(), ls::getTileSize());
    //loop through all the ground tiles
    for (auto w : walls) {
        auto pos = ls::getTilePosition(w);
        pos += Vector2f(16.f, 16.f);
        //ls::Tile t = ls::getTile({pos.x, pos.y});
        tp temp;
        temp.p = pos;
        temp.s = tls;
        tps.push_back(temp);
    }

    const auto nonempty = tps.size();

    //if tile 1 is touching tile 2
    //we can use one large body instead of 2
    if (nonempty) {
        std::vector<tp> tpo;
        tp last = tps[0];
        size_t samecount = 0;

        for (size_t i = 1; i < nonempty; ++i) {
            //is this tile compressible with the last?
            bool same = ((tps[i].p.y == last.p.y) &&
                         tps[i].p.x == last.p.x + (tls.x * (1 + samecount)));
            if (same) {
                ++samecount;
            } else {
                if (samecount) {
                    last.s.x = (1 + samecount) * tls.x; //expand tile
                }
                //write tile to list
                tpo.push_back(last);
                samecount = 0;
                last = tps[i];
            }
        }
        //catch the last tile
        if (samecount) {
            last.s.x = (1 + samecount) * tls.x;
            tpo.push_back(last);
        }

        const auto xsave = tpo.size();
        samecount = 0;
        std::vector<tp> tpox;
        for (size_t i = 0; i < tpo.size(); ++i) {
            last = tpo[i];
            for (size_t j = i + 1; j < tpo.size(); ++j) {
                bool same = ((tpo[j].p.x == last.p.x) && (tpo[j].s == last.s) &&
                             (tpo[j].p.y == last.p.y + (tls.y * (1 + samecount))));
                if (same) {
                    ++samecount;
                    tpo.erase(tpo.begin() + j);
                    --j;
                }
            }
            if (samecount) {
                last.s.y = (1 + samecount) * tls.y; // Expand tile
            }
            // write tile to list
            tpox.push_back(last);
            samecount = 0;
        }

        tps.swap(tpox);
    }
    for (auto &t : tps) {
        LOG(DEBUG) << "HERE" << t.p;

        auto s = scene->makeEntity();
        s->setPosition(t.p);
        s->addComponent<PhysicsComponent>(false, t.s);
    }
    */
}

std::shared_ptr<Entity> EntityFactory::makeSpawner(Scene *scene, const sf::Vector2f &pos) {
    auto spawner = scene->makeEntity();
    spawner->setPosition(pos);
    spawner->addComponent<SpawnerComponent>();

    auto anim = spawner->addComponent<AnimatedSpriteComponent>(Vector2f(32.f, 32.f));
    anim->setSpritesheet(TextureManager::getTexture("slime.png"));

    return spawner;
}

//auto e = scene->makeEntity();
// e->setPosition(pos);
//e->addComponent<PhysicsComponent>(false, Vector2f(32.f, 32.f));

