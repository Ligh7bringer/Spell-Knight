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

void MenuScene::Load() {
    _delay = 0.3f;
    resetView();

    _background = Sprite(TextureManager::getTexture("menu-bg-2.png"));
    _background.setOrigin(Vector2f(_background.getTexture()->getSize()) / 2.f);
    _background.setPosition(Vector2f(Engine::getWindowSize()) / 2.f);

    _mainMenu = Menu();
    _mainMenu.setPosition(Vector2f(500, 200));
    _mainMenu.addTitle("Spell Knight");
    _mainMenu.setTitleSize(45);
    _mainMenu.addButton(Config::getLocalisedString("play")); //id=0
    _mainMenu.addButton(Config::getLocalisedString("options")); //id=1
    _mainMenu.addButton(Config::getLocalisedString("hiscore")); //id=2
    _mainMenu.addButton(Config::getLocalisedString("exit")); //id=3

    setLoaded(true);
}

void MenuScene::Update(const double& dt) {
    _delay -= static_cast<float>(dt);
    if(_delay < 0)
        _mainMenu.update(dt);

    if(_mainMenu.getMenuResponse() == 0) { //play button
        Engine::ChangeScene((Scene*)&level1);
    }
    if(_mainMenu.getMenuResponse() == 1) { //options button
        Engine::ChangeScene((Scene*)&options);
    }
    if(_mainMenu.getMenuResponse() == 2) { //exit button
        //exit
        Engine::ChangeScene((Scene*)&highScore); //high score btn
    }
    if(_mainMenu.getMenuResponse() == 3) { //exit button
        //exit
        Engine::Exit();
    }

    Scene::Update(dt);
}

void MenuScene::Render() {
    //make sure background is drawn before the menu
    Engine::GetWindow().draw(_background);
    _mainMenu.render();
    Scene::Render();
}
