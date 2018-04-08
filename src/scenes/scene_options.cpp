#include "scene_options.h"
#include "../../engine/lib_settings_parser/settings_parser.h"
#include "../game.h"
#include "../Log.h"
#include <string>

using namespace std;
using namespace sf;

SettingsParser options_languageFile;

void OptionsScene::Load() {
    _timer = 0.5f;
    Vector2f windowSize(Engine::getWindowSize());
    auto center = windowSize / 2.f;
    _view = View(center, windowSize);
    Engine::setView(_view);
    options_languageFile.readFile("res/lang/en.txt");

    Vector2f pos(Vector2f(500, 200));
    _optionsMenu = Menu();
    _optionsMenu.addTitle(pos, Vector2f(100, 100), options_languageFile.get("options"));

    std::vector<std::string> languages = { "English", "Bulgarian" };
    std::vector<std::string> resolutions = { "1366 x 768", "1280 x 760", "800 x 600" };

    _optionsMenu.addOptionButton(Vector2f(pos.x, pos.y+150), Vector2f(200.f, 35.f), languages); //id=0
    _optionsMenu.addOptionButton(Vector2f(pos.x, pos.y+200), Vector2f(200.f, 35.f), resolutions); //id=1
    _optionsMenu.addButton(Vector2f(pos.x, pos.y+250), Vector2f(200.f, 35.f), "walk left"); //id=2
    _optionsMenu.addLabel(0, "language:");
    _optionsMenu.addLabel(1, "resolution:");
    _optionsMenu.addLabel(2, "A");

    _optionsMenu.addButton(Vector2f(800, 360), Vector2f(200.f, 35.f), "Main menu"); //id=3

    setLoaded(true);
}

void OptionsScene::Update(const double& dt) {
    _optionsMenu.update(dt);
    Scene::Update(dt);

    if(_optionsMenu.getMenuResponse() == 1) {
        LOG(DEBUG) << _optionsMenu.getSelectedOption(1);
    }
    if(_optionsMenu.getMenuResponse() == 2) {
       updateLabel(2, dt);
    }

    if(_optionsMenu.getMenuResponse() == 3) {
        Engine::ChangeScene((Scene*)&menu);
    }
}

void OptionsScene::Render() {
    _optionsMenu.render();
    Scene::Render();
}

void OptionsScene::updateLabel(unsigned int id, double dt) {
    while(_timer > 0) {
        auto keys = Engine::getKeys();
        if (!keys.empty()) {
            string s(1, keys[0]);
            _optionsMenu.addLabel(id, s);
        }
        _timer -= dt;
    }
}
