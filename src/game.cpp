#include "game.h"
#include "system_renderer.h"
#include "levelsystem.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "ecm.h"

using namespace std;
using namespace sf;

Font font;
Text text;

//Menu scene
MenuScene::MenuScene() {}

void MenuScene::Load() {
    if(!font.loadFromFile("res/fonts/college.ttf")) {
        cerr << "Couldn't load font!" << endl;
    }
    text.setString("Main Menu");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setPosition(50, 50);
}

void MenuScene::Update(double dt) {
    if(Keyboard::isKeyPressed(Keyboard::Space)) {
        activeScene = gameScene;
    }

    Scene::Update(dt);
}

void MenuScene::Render() {
    Renderer::queue(&text);

    Scene::Render();
}

//Game scene
GameScene::GameScene() {}

void GameScene::Respawn() {}

void GameScene::Load() {
    LevelSystem::loadLevelFile("res/levels/level_1", 25.0f);

    auto player = make_shared<Entity>();
    auto s = player->addComponent<ShapeComponent>();
    s->setShape<sf::CircleShape>(10.0f);
    s->getShape().setFillColor(Color::Green);
    s->getShape().setOrigin(Vector2f(10.f, 10.f));
   
    auto m = player->addComponent<PlayerMovementComponent>();
    m->setSpeed(100.0f);
    _ents.list.push_back(player);
}

void GameScene::Update(double dt) {
    if(Keyboard::isKeyPressed(Keyboard::Tab)) {
        activeScene = menuScene;
    }

    Scene::Update(dt);
}

void GameScene::Render() {
    LevelSystem::Render(Renderer::getWindow());

    Scene::Render();
}