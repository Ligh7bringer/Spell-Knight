#include "entity_factory.h"
#include "components/cmp_player_physics.h"
#include "components/cmp_animated_sprite.h"
#include "components/cmp_enemy_ai.h"
#include "components/cmp_hurt_player.h"
#include "components/cmp_player_lives.h"
#include "components/cmp_player_bullet.h"
#include "components/cmp_enemy_physics.h"
#include "components/cmp_physics.h"
#include "../engine/lib_tile_level_loader/LevelSystem.h"
#include "../engine/lib_texture_manager/TextureManager.h"
#include "components/cmp_pickup.h"
#include "components/cmp_score.h"
#include "Log.h"
#include "components/cmp_enemy_health.h"

using namespace sf;

/*
* Factory class for easier creation of entities.
*/

//creates the player at position pos in Scene scene
std::shared_ptr<Entity> EntityFactory::makePlayer(Scene* scene, const Vector2f& pos) {
    auto player = scene->makeEntity();
    player->setPosition(pos);
    player->addTag("player");
  
    auto anim = player->addComponent<AnimatedSpriteComponent>(64, 64);
    anim->setSpritesheet(TextureManager::getTexture("WIZARD.png"));
    anim->setNumberOfFrames(4);
    anim->setSpriteSheetPadding(2);
    anim->setFrameTime(0.2f);
    player->addComponent<PlayerPhysicsComponent>(Vector2f(27.f, 62.f));
    player->addComponent<PlayerBulletComponent>();
    player->addComponent<PlayerLivesComponent>(3);
    player->addComponent<PlayerScoreComponent>();

    return player;
}

//creates a snake enemy at position pos in Scene scene
std::shared_ptr<Entity> EntityFactory::makeSlime(Scene* scene, const Vector2f& pos) {
    auto slime = scene->makeEntity();
    slime->addTag("enemy");
    // set position
    slime->setPosition(pos);
    auto anim = slime->addComponent<AnimatedSpriteComponent>(32, 32);
    anim->setSpritesheet(TextureManager::getTexture("slime.png"));
    anim->setNumberOfFrames(4);
    // Add HurtComponent
    slime->addComponent<HurtComponent>();
    slime->addComponent<EnemyHealthComponent>(1);
    // Add EnemyAIComponent
    //slime->addComponent<EnemyAIComponent>();
	slime->addComponent<EnemyPhysicsComponent>(Vector2f(32.f, 32.f), false);
    //auto physics = slime->addComponent<PhysicsComponent>(true, Vector2f(32.f, 32.f));
    //physics->setLinearVelocity(Vector2f(10.f, 0.f));

    return slime;
}

//creates an eye demon enemy at position pos in Scene scene
std::shared_ptr<Entity> EntityFactory::makeEyeDemon(Scene* scene, const sf::Vector2f& pos) {
    auto eyeDemon = scene->makeEntity();
    eyeDemon->addTag("enemy");
    eyeDemon->setPosition(pos);
    auto anim = eyeDemon->addComponent<AnimatedSpriteComponent>(64, 37);
    anim->setSpritesheet(TextureManager::getTexture("sheet_eye_flyer.png"));
    anim->setNumberOfFrames(5);
    eyeDemon->addComponent<HurtComponent>();
    //eyeDemon->addComponent<EnemyAIComponent>();
    eyeDemon->addComponent<EnemyPhysicsComponent>(Vector2f(64.f, 37.f), true);
    eyeDemon->addComponent<EnemyHealthComponent>(4);

    return eyeDemon;
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

        //auto e = scene->makeEntity();
       // e->setPosition(pos);
        //e->addComponent<PhysicsComponent>(false, Vector2f(32.f, 32.f));

//makes a collectible in Scene scene at position pos
std::shared_ptr<Entity> EntityFactory::makePowerUp(Scene* scene, sf::Vector2f& pos) {
    auto pu = scene->makeEntity();
    pu->addTag("flame");
    pu->setPosition(pos);
    pu->addComponent<PickUpComponent>();

    auto anim = pu->addComponent<AnimatedSpriteComponent>(32, 32);
    anim->setSpritesheet(TextureManager::getTexture("flame.png"));
    anim->setNumberOfFrames(4);
    anim->setFrameTime(0.1f);

    return pu;
}