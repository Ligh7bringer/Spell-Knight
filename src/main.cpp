#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "system_renderer.h"

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;

std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

void Reset() {}

void Load() {
	gameScene = make_shared<GameScene>();
	menuScene = make_shared<MenuScene>();
	gameScene.reset(new GameScene());
	menuScene.reset(new MenuScene());
	activeScene = menuScene;
	gameScene->Load();
	menuScene->Load();
}

void Update(RenderWindow &window) {
	// recalculate delta time
	static Clock clock;
	float dt = clock.restart().asSeconds();
	//check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	activeScene->Update(dt);
}

void Render(RenderWindow &window) {
	activeScene->Render();

	Renderer::render();
}

  int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Coursework");
	Renderer::initiliase(window);
	Load();

	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}

    return 0;
  }
