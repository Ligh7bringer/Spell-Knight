#include "scene_level1.h"
#include "../game.h"
#include <LevelSystem.h>
#include <thread>
#include "system_renderer.h"
#include "../misc/entity_factory.h"
#include "../Log.h"
#include "../components/cmp_score.h"
#include "../components/cmp_timer.h"
#include "../../engine/lib_audio_manager/audio_manager.h"

using namespace std;
using namespace sf;

//Sprite background;	

static shared_ptr<Entity> player;
int score;
int playerTime;

void Level1Scene::Load() {
    AudioManager::initialise();
    AudioManager::playMusic("background.wav", true);

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
    auto slimePos = LevelSystem::getPosition(LevelSystem::enemyTiles::SLIME);
    for(int i = 0; i < slimePos.size(); i+=2) {
        auto start = slimePos[i];
        auto end = slimePos[i+1];
        auto distance = end - start;
        EntityFactory::makeSlime(this, start, distance, 1.5f);
    }

    auto eyePos = LevelSystem::getPosition(LevelSystem::enemyTiles::EYE);
    for(auto ep : eyePos) {
        EntityFactory::makeEyeDemon(this, ep);
    }

    auto plantPos = LevelSystem::getPosition(LevelSystem::enemyTiles::PLANT);
    for(auto pp : plantPos) {
        EntityFactory::makePlant(this, pp);
    }

    auto birdPos = LevelSystem::getPosition(LevelSystem::enemyTiles::BIRD);
    for(auto bp : birdPos) {
        EntityFactory::makeCloud(this, bp);
    }

    // Add physics coliders to level tiles.
    EntityFactory::makeWalls(this);

    //create a power up
    auto flamePos = ls::getPosition(ls::groundTiles::COIN);
    for (auto fp : flamePos) {
        EntityFactory::makePowerUp(this, fp);
    }

    //make fish
    auto waterTiles = LevelSystem::getPosition(ls::baseTiles::DEADFALL);
    auto fishPos = waterTiles[2];
    EntityFactory::makeFish(this, fishPos);

    //get positions of moving tiles
    auto platformTile = LevelSystem::getPosition(ls::platformTiles::PLATFORM_MOVING);
    //create platforms
    for(int i = 0; i < platformTile.size(); i+= 2) {
        //for every two positions
        //the first one is the starting position
        auto start = platformTile[i];
        //the second one is the destination position
        auto end = platformTile[i + 1];
        //distance is end - start
        auto distance = end - start;
        EntityFactory::makeMovingPlatform(this, start, distance, 2.f);
    }

    //make falling platform
    platformTile = LevelSystem::getPosition(ls::platformTiles::PLATFORM_FALLING);
    auto platformPos = platformTile[0];
    EntityFactory::makeFallingPlatform(this, platformPos);

    //create boulder spawner
    EntityFactory::makeSpawner(this, LevelSystem::getPosition(LevelSystem::enemyTiles::BOULDER)[0]);

    //create spikes
    auto spikePos = LevelSystem::getPosition(LevelSystem::enemyTiles::SPIKE);
    for(auto sp : spikePos)
        EntityFactory::makeSpike(this, sp);

    LOG(INFO) << "Scene 1 Restarted!";
}

void Level1Scene::UnLoad() {
    cout << "Scene 1 Unload" << endl;
    AudioManager::stopMusic("background.wav");
    //don't forget to reset to default view or when the scene is changed or nothing is visible :D
    Renderer::resetView();
    player.reset();
    ls::unload();
    Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {
    _parBackground.update(dt);

    //show game over scene if player dies
    if (!player->isAlive()) {
        AudioManager::playSound("death.wav");
        gameOver.setText("Game over!");
        Engine::ChangeScene(&gameOver);
    } else {
        auto timeComp = player->get_components<TimerComponent>()[0];
        playerTime = timeComp->getTime();
        auto scoreComp = player->get_components<PlayerScoreComponent>()[0];
        score = scoreComp->getPoints();
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

    Scene::Update(dt);
}

void Level1Scene::Render() {
    _parBackground.render();

    ls::render(Engine::GetWindow());

    Scene::Render();
}


