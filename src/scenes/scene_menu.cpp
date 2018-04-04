#include "scene_menu.h"
#include "../game.h"
#include "../GUI/menu.h"
#include "../../engine/lib_settings_parser/settings_parser.h"

using namespace std;
using namespace sf;

Menu mainMenu;
Panel title;

void MenuScene::Load() {
  SettingsParser settings;
  settings.readFile("res/lang/en.txt");

  mainMenu = Menu();
  title = Panel(Vector2f(500, 200), Vector2f(100, 100), "Anonymous.ttf");
  title.setGUI(false);
  title.setPanelColour(Color::Transparent);
  title.setTextLocalised(settings.get("title"));
  title.setTextColour(Color::White);

  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  mainMenu.update(dt);
  title.update(dt);

  if(mainMenu.getMenuResponse() == Menu::PLAY) {
    Engine::ChangeScene((Scene*)&level1);
  } 
  if(mainMenu.getMenuResponse() == Menu::OPTIONS) {
    //to do
  }
  if(mainMenu.getMenuResponse() == Menu::EXIT) {
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
