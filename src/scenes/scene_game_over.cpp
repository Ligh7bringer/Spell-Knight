#include "scene_game_over.h"
#include <SFML/Window/Keyboard.hpp>
#include "../game.h"
#include "../Log.h"

using namespace sf;

//initialise panel
void GameOverScene::Load() {
    auto pos = static_cast<Vector2f>(Engine::getWindowSize()) / 2.f;
    _panel = Panel(pos, Vector2f(600.f, 200.f), "DoctorSoos.ttf");
    _panel.setPositionOfCentre(pos);
    _panel.setTextSize(40);
    _panel.setGUI(false);
    setLoaded(true);
}

void GameOverScene::Update(const double& dt) {
    //for some reason if the text is set in load the score and time are always 0
    _panel.setTextLocalised(_message + "\nScore: " + std::to_string(score) + "\nTime: " + std::to_string(playerTime) + "s");

    //allow the user to go back to the menu or restart the level
    if(Keyboard::isKeyPressed(Keyboard::Return)) {
        Engine::ChangeScene(&level1);
    }

    if(Keyboard::isKeyPressed(Keyboard::Escape)) {
        Engine::ChangeScene(&menu);
    }

    //update everything else
    _panel.update(dt);
    Scene::Update(dt);
}

//render
void GameOverScene::Render() {
    _panel.render();

    Scene::Render();
}

//reset variables
void GameOverScene::UnLoad() {
    score = 0;
    playerTime = 0;
}

//sets the message to be displayed
//just so we don't need saparate rooms for game over and level complete 
//the only difference between them would be the displayed text
void GameOverScene::setText(const std::string& text) {
    _message = text;
}
