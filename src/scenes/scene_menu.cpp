#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../button.h"

using namespace std;
using namespace sf;

Button play;

void MenuScene::Load() {
  cout << "Menu Load \n";
  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(
        "Platformer\nPress Space to Start");
  }
  setLoaded(true);

  play = Button(Vector2f(100, 50), "PLAY");
  play.setPosition(Vector2f(500, 500));
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
    Engine::ChangeScene(&level1);
  }

  play.update(dt);
  if(play.isClicked()) {
      Engine::ChangeScene(&level1);
  }

  Scene::Update(dt);
}

void MenuScene::Render() {
  play.render();

  Scene::Render();
}
