#include <input_manager.h>
#include "scene_options.h"
#include "../../engine/lib_settings_parser/settings_parser.h"
#include "../game.h"
#include "../Log.h"

using namespace std;
using namespace sf;

SettingsParser options_languageFile;

void OptionsScene::Load() {
    _delay = 0.3f;
    initResolutions();
    initActions();

    Vector2f windowSize(Engine::getWindowSize());
    auto center = windowSize / 2.f;
    _view = View(center, windowSize);
    Engine::setView(_view);

    _flag = false;
    options_languageFile.readFile("res/lang/en.txt");

    Vector2f pos(Vector2f(500, 200));
    _optionsMenu = Menu();
    _optionsMenu.setPosition(Vector2f(pos));
    _optionsMenu.addTitle(options_languageFile.get("options"));

    std::vector<std::string> languages = { "English", "Bulgarian" };
    std::vector<std::string> resolutions = { "1280 x 760", "800 x 600", "1366 x 768" };
    std::vector<std::string> fullscreen = { "Windowed", "Fullscreen"};

    _optionsMenu.addOptionButton(languages); //id=0
    _optionsMenu.addOptionButton(resolutions); //id=1
    _optionsMenu.addOptionButton(fullscreen); //id=2
    _optionsMenu.addButton("Walk left"); //id=3
    _optionsMenu.addButton("Walk right"); //id=4
    _optionsMenu.addButton("Jump"); //id=5
    _optionsMenu.addButton("Shoot"); //id=6
    _optionsMenu.addButton("Main menu"); //id=7

    _optionsMenu.addLabel(0, "Language:");
    _optionsMenu.addLabel(1, "Resolution:");
    _optionsMenu.addLabel(2, "Window mode:");
    _optionsMenu.addLabel(3, "Key bindings :");

    setLoaded(true);
}

void OptionsScene::Update(const double& dt) {
    _delay -= dt;
    if(_delay <= 0) {
        _optionsMenu.update(dt);
    }

   switch(_optionsMenu.getMenuResponse()) {
       case 0:
           break;
       case 1: //resolution button pressed; set the correct resolution
           Engine::setResolution(_resolutionData[_optionsMenu.getSelectedOption(1)]);
           break;
       case 2: //fullscreen btn pressed, toggle fullscreen
           Engine::toggleFullscreen();
           break;
       case 3:
           updateButton(3);
           break;
       case 4:
           updateButton(4);
           break;
       case 5:
           updateButton(5);
           break;
       case 6:
           updateButton(6);
           break;
       case 7:
           Engine::ChangeScene((Scene*)&menu);
           break;
       default:
           break;
   }

    if (_flag) {
        auto keys = Engine::getKeysText();
        if (!keys.empty()) {
            InputManager::addKey(_actionData[_id], Event::KeyPressed, Engine::getKeys()[0]);
            _optionsMenu.addLabel(_id, "Done!");
            _flag = false;
        }
    }

    Scene::Update(dt);
}

void OptionsScene::Render() {
    _optionsMenu.render();
    Scene::Render();
}

void OptionsScene::initResolutions() {
    _resolutionData["1366 x 768"] = Vector2f(1366, 768);
    _resolutionData["1280 x 760"] = Vector2f(1280, 760);
    _resolutionData["800 x 600"] = Vector2f(800, 600);
}

void OptionsScene::initActions() {
    _actionData[3] = "walkLeft";
    _actionData[4] = "walkRight";
    _actionData[5] = "jump";
    _actionData[6] = "shoot";
}

void OptionsScene::updateButton(unsigned int id) {
    _flag = true;
    _id = id;
    _optionsMenu.addLabel(id, "Press any key");
}
