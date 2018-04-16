#include <texture_manager.h>
#include <system_renderer.h>
#include "scene_menu.h"
#include "../game.h"
#include "../../engine/lib_settings_parser/settings_parser.h"
#include "../Log.h"
#include "../config.h"
#include "../components/cmp_animated_sprite.h"

using namespace std;
using namespace sf;

sf::Sprite _bg;

void MenuScene::Load() {
    Vector2f windowSize(Engine::getWindowSize());
    auto center = windowSize / 2.f;
    _view = View(center, windowSize);
    Engine::setView(_view);

    _bg = Sprite(TextureManager::getTexture("menu-bg-2.png"));
    _bg.setOrigin(Vector2f(_bg.getTexture()->getSize()) / 2.f);
    _bg.setPosition(center);

    _mainMenu = Menu();
    _mainMenu.setPosition(Vector2f(500, 200));
    _mainMenu.addTitle("Spell Knight");
    _mainMenu.setTitleSize(45);
    _mainMenu.addButton(Config::getLocalisedString("play")); //id = 0
    _mainMenu.addButton(Config::getLocalisedString("options")); //id = 1
    _mainMenu.addButton(Config::getLocalisedString("exit")); //id = 2

    setLoaded(true);
}

void MenuScene::Update(const double& dt) {
    _parBackground.update(dt);
    _mainMenu.update(dt);

    if(_mainMenu.getMenuResponse() == 0) { //play button
        Engine::ChangeScene((Scene*)&level1);
    }
    if(_mainMenu.getMenuResponse() == 1) { //options button
        Engine::ChangeScene((Scene*)&options);
    }
    if(_mainMenu.getMenuResponse() == 2) {
        //exit
        Engine::Exit();
    }

    Scene::Update(dt);
}

void MenuScene::Render() {
    //make sure background is drawn before the menu
    Engine::GetWindow().draw(_bg);
    _mainMenu.render();
    Scene::Render();
}
