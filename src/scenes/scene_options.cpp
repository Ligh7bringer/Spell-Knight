#include "scene_options.h"
#include "../../engine/lib_settings_parser/settings_parser.h"
#include "../GUI/menu.h"

using namespace std;
using namespace sf;

Menu optionsMenu;
SettingsParser options_settingsFile;
SettingsParser options_languageFile;

void OptionsScene::Load() {
  options_settingsFile.readFile("res/settings.cfg");
  options_languageFile.readFile(options_settingsFile.get("language"));
  Vector2f pos(Vector2f(500, 200));
  optionsMenu = Menu();
  optionsMenu.addTitle(pos, Vector2f(100, 100), options_languageFile.get("options"));
  optionsMenu.addButton(Vector2f(pos.x, pos.y+150), Vector2f(200.f, 35.f)
                                  , options_languageFile.get("language"));
  optionsMenu.addButton(Vector2f(pos.x, pos.y+200), Vector2f(200.f, 35.f)
          , options_settingsFile.get("width") +" X " + options_settingsFile.get("height"));

  optionsMenu.addLabel(0, "language: ");
  optionsMenu.addLabel(1, "resolution: ");
  setLoaded(true);
}

void OptionsScene::Update(const double& dt) {
  optionsMenu.update(dt);
  Scene::Update(dt);
}

void OptionsScene::Render() {
  optionsMenu.render();
  Scene::Render();
}
