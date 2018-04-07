#include "scene_menu.h"
#include "../game.h"
#include "../GUI/menu.h"
#include "../../engine/lib_settings_parser/settings_parser.h"

using namespace std;
using namespace sf;

Menu mainMenu;
Panel title;
SettingsParser settingsFile;
SettingsParser languageFile;

void MenuScene::Load() {
    settingsFile.readFile("res/settings.cfg");
    languageFile.readFile(settingsFile.get("language"));

    mainMenu = Menu();
    mainMenu.addButton(Vector2f(500, 350), Vector2f(200, 35), languageFile.get("play"));
    mainMenu.addButton(Vector2f(500, 400), Vector2f(200, 35), languageFile.get("options"));
    mainMenu.addButton(Vector2f(500, 450), Vector2f(200, 35), languageFile.get("exit"));

    title = Panel(Vector2f(500, 200), Vector2f(100, 100), "Anonymous.ttf");
    title.setGUI(false);
    title.setPanelColour(Color::Transparent);
    title.setTextLocalised(languageFile.get("title"));
    title.setTextColour(Color::White);

    setLoaded(true);
}

void MenuScene::Update(const double& dt) {
    mainMenu.update(dt);
    title.update(dt);

    if(mainMenu.getMenuResponse() == 0) {
        Engine::ChangeScene((Scene*)&level1);
    }
    if(mainMenu.getMenuResponse() == 1) {
        Engine::ChangeScene((Scene*)&options);
    }
    if(mainMenu.getMenuResponse() == 2) {
        //exit
        Engine::Exit();
    }

    Scene::Update(dt);
}

void MenuScene::Render() {
    mainMenu.render();
    title.render();

    Scene::Render();
}
