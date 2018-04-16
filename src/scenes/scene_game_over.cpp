#include "scene_game_over.h"
#include "../game.h"
#include "../Log.h"
#include "../config.h"

using namespace sf;

//initialise panel
void GameOverScene::Load() {
    _init = true;
    _timer = 0.3f;
    resetView();

    Vector2f pos(Engine::getWindowSize());
    pos /= 2.f;
    _panel = Panel(pos, Vector2f(600.f, 200.f));
    _panel.setPositionOfCentre(pos);
    _panel.setTextSize(40);
    _panel.setGUI(false);
    _panel.setPanelColour(Color(102, 178, 255));

    restartLevelbtn = Button(Vector2f(pos.x-100, pos.y+100), Vector2f(200.f, 35.f), Config::getLocalisedString("restart"));
    mainMenubtn = Button(Vector2f(pos.x-300, pos.y+100), Vector2f(200.f, 35.f), Config::getLocalisedString("main_menu"));

    setLoaded(true);
}

void GameOverScene::Update(const double& dt) {
    _timer -= dt;
    if(_init && _timer < 0) {
        //for some reason if the text is set in load the score and time are wrong
        Config::updateHighScore();
        _init = false;
    }

    _panel.setTextLocalised(_message + "\nScore: " + std::to_string(Config::get_score()) + "\nTime: " + std::to_string(Config::get_time()) + "s");

    nextLevelbtn.update(dt);
    restartLevelbtn.update(dt);
    mainMenubtn.update(dt);
    //allow the user to go back to the menu or restart the level
    if(Keyboard::isKeyPressed(Keyboard::Return) || restartLevelbtn.isClicked()) {
        Engine::ChangeScene((Scene*)&level1);
        //Engine::ChangeScene((Scene*)&currentLevel)
    }

    if(Keyboard::isKeyPressed(Keyboard::Escape) || mainMenubtn.isClicked()) {
        Engine::ChangeScene((Scene*)&menu);
    }
    if(nextLevelbtn.isClicked()){
        //Engine::ChangeScene((Scene*)&level1);
        //Engine::ChangeScene((Scene*)&level(levelInt++))
    }
    //update everything else
    _panel.update(dt);
    Scene::Update(dt);
}

//render
void GameOverScene::Render() {
    _panel.render();
    nextLevelbtn.render();
    restartLevelbtn.render();
    mainMenubtn.render();
    Scene::Render();
}

//reset variables
void GameOverScene::UnLoad() {
    Config::set_score(0);
    Config::set_time(0);
}

//sets the message to be displayed
//just so we don't need saparate rooms for game over and level complete 
//the only difference between them would be the displayed text
void GameOverScene::setText(const std::string& text) {
    _message = text;
}

void GameOverScene::nextLevel(){
  // maybe check if there is a next level and if there isnt
  // another level then dont render next level btn
  Vector2f pos(Engine::getWindowSize());
  pos /= 2.f;
  nextLevelbtn = Button(Vector2f(pos.x+100, pos.y+100), Vector2f(200.f, 35.f), Config::getLocalisedString("next_level"));
}
