#include "scene_menu.h"
#include "../game.h"
#include "../../engine/lib_settings_parser/settings_parser.h"
#include "../Log.h"

using namespace std;
using namespace sf;

SettingsParser languageFile;

void MenuScene::Load() {
    Vector2f windowSize(Engine::getWindowSize());
    auto center = windowSize / 2.f;
    _view = View(center, windowSize);
    Engine::setView(_view);

    languageFile.readFile("res/lang/en.txt");

    _mainMenu = Menu();
    _mainMenu.setPosition(Vector2f(500, 200));
    _mainMenu.addTitle("Spell Knight");
    _mainMenu.addButton(languageFile.get("play")); //id = 0
    _mainMenu.addButton(languageFile.get("options")); //id = 1
    _mainMenu.addButton(languageFile.get("exit")); //id = 2

    setLoaded(true);
}

void MenuScene::Update(const double& dt) {
    _mainMenu.update(dt);

    if(_mainMenu.getMenuResponse() == 0) {
        Engine::ChangeScene((Scene*)&level1);
    }
    if(_mainMenu.getMenuResponse() == 1) {
        Engine::ChangeScene((Scene*)&options);
    }
    if(_mainMenu.getMenuResponse() == 2) {
        //exit
        Engine::Exit();
    }

    Scene::Update(dt);
}

void MenuScene::Render() {
    _mainMenu.render();
    Scene::Render();
}
