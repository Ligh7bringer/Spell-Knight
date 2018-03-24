#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include "../Log.h"
#include "../GUI/button.h"
#include "../GUI/menu.h"
#include "../../engine/src/engine.h"

using namespace std;
using namespace sf;

Menu mainMenu;
Panel title;

void MenuScene::Load() {
  mainMenu = Menu();
  title = Panel(Vector2f(500, 200), Vector2f(100, 100), "DoctorSoos.ttf");
  title.setPanelColour(Color::Transparent);
  title.setText("Spell Knight");
  title.setTextColour(Color::White);

  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";
  mainMenu.update(dt);
  title.update(dt);

  if(mainMenu.getMenuResponse() == Menu::PLAY) {
    Engine::ChangeScene(&level1);
  } 
  if(mainMenu.getMenuResponse() == Menu::OPTIONS) {
    //go to options scene
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
