#include "scene_options.h"
#include "../../engine/lib_settings_parser/settings_parser.h"
#include "../GUI/menu.h"

using namespace std;
using namespace sf;

Menu optionsMenu;
SettingsParser options_languageFile;

void OptionsScene::Load() {
    options_languageFile.readFile("res/lang/en.txt");
    Vector2f pos(Vector2f(500, 200));
    optionsMenu = Menu();
    optionsMenu.addTitle(pos, Vector2f(100, 100), options_languageFile.get("options"));

    std::vector<std::string> languages = { "English", "Bulgarian"};
    optionsMenu.addOptionButton(Vector2f(pos.x, pos.y+150), Vector2f(200.f, 35.f), languages);
    std::vector<std::string> resolutions = { "1366 x 768", "1280 x 760", "800 x 600"};
    optionsMenu.addOptionButton(Vector2f(pos.x, pos.y+200), Vector2f(200.f, 35.f), resolutions);

    optionsMenu.addLabel(0, "language:");
    optionsMenu.addLabel(1, "resolution:");

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
