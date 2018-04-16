#include <input_manager.h>
#include <texture_manager.h>
#include "scene_options.h"
#include "../game.h"
#include "../config.h"

using namespace std;
using namespace sf;

Sprite _background;

void OptionsScene::Load() {
    _sceneID = "options";
    _delay = 0.3f;

    initResolutions();
    initActions();
    initLang();

    Vector2f windowSize(Engine::getWindowSize());
    auto center = windowSize / 2.f;
    _view = View(center, windowSize);
    Engine::setView(_view);

    _background = Sprite(TextureManager::getTexture("options-bg.jpg"));
    _background.setOrigin(Vector2f(_background.getTexture()->getSize()) / 2.f);
    _background.setPosition(center);

    _flag = false;

    Vector2f pos(Vector2f(500, 200));
    _optionsMenu = Menu();
    _optionsMenu.setPosition(Vector2f(pos));
    _optionsMenu.addTitle(Config::getLocalisedString("options"));

    std::vector<std::string> languages = { "en.txt", "bg.txt" };
    std::vector<std::string> resolutions = { "1280 x 720", "720 x 480", "1366 x 768", "1920 x 1080" };

    _optionsMenu.addOptionButton(languages); //id=0
    _optionsMenu.setSelection(0, Config::getSetting("language"));
    _optionsMenu.addOptionButton(resolutions); //id=1
    auto res_str = Config::getSetting("width") + " x " + Config::getSetting("height");
    _optionsMenu.setSelection(1, res_str);
    _optionsMenu.addButton(Config::getLocalisedString("toggle")); //id=2
    _optionsMenu.addButton(Config::getLocalisedString("walkl")); //id=3
    _optionsMenu.addButton(Config::getLocalisedString("walkr")); //id=4
    _optionsMenu.addButton(Config::getLocalisedString("jump")); //id=5
    _optionsMenu.addButton(Config::getLocalisedString("shoot")); //id=6
    _optionsMenu.addButton(Config::getLocalisedString("main_menu")); //id=7

    _optionsMenu.addLabel(0, Config::getLocalisedString("language"));
    _optionsMenu.addLabel(1, Config::getLocalisedString("resolution"));
    _optionsMenu.addLabel(2, Config::getLocalisedString("winmode"));
    _optionsMenu.addLabel(3, Config::getLocalisedString("bindings"));

    setLoaded(true);
}

void OptionsScene::Update(const double& dt) {
    _delay -= dt;
    if(_delay <= 0) {
        _optionsMenu.update(dt);
    }

   switch(_optionsMenu.getMenuResponse()) {
       case 0:
           {
               string selection = _optionsMenu.getSelectedOption(0);
               Config::setCurrentLanguage(_langData[selection]);
               Config::setSetting("language", _langData[selection]);
               break;
           }
       case 1: //resolution button pressed; set the correct resolution
	   {
		   Engine::setResolution(_resolutionData[_optionsMenu.getSelectedOption(1)]);
		   _optionsMenu.repositionMenu();
		   Vector2f windowSize(Engine::getWindowSize());
		   auto center = windowSize / 2.f;
		   _view = View(center, windowSize);
		   Engine::setView(_view);
		   break;
	   }
           
       case 2: //fullscreen btn pressed, toggle fullscreen
           Engine::toggleFullscreen();
            Config::setSetting("fullscreen", Engine::isFullscreen() ? "1" : "0");
           _optionsMenu.repositionMenu();
           break;
       case 3: //key bindings buttons:
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
           break; //end of key bindings
       case 7: //back button
           Engine::ChangeScene((Scene*)&menu);
           break;
       default:
           break;
   }

    if (_flag && !Engine::getKeys().empty()) {
        InputManager::addKey(_actionData[_id], Event::KeyPressed, Engine::getKeys()[0]);
        _optionsMenu.addLabel(_id, Config::getLocalisedString("done"));
        _flag = false;
        Config::setSetting(_actionData[_id], to_string(InputManager::getKey(_actionData[_id])));
    }

    Scene::Update(dt);
}

void OptionsScene::Render() {
    Engine::GetWindow().draw(_background);
    _optionsMenu.render();
    Scene::Render();
}

void OptionsScene::initResolutions() {
    _resolutionData["1366 x 768"] = Vector2u(1366, 768);
    _resolutionData["1280 x 720"] = Vector2u(1280, 720);
    _resolutionData["720 x 480"] = Vector2u(720, 480);
    _resolutionData["1920 x 1080"] = Vector2u(1920, 1080);
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
    _optionsMenu.addLabel(id, Config::getLocalisedString("anykey"));
}

void OptionsScene::initLang() {
    _langData["en.txt"] = "en.txt";
    _langData["bg.txt"] = "bg.txt";
}
