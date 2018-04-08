#include "scene_game_over.h"
#include "../game.h"
#include "../Log.h"
#include "../../engine/lib_settings_parser/settings_parser.h"
using namespace sf;

SettingsParser languages;

//initialise panel
void GameOverScene::Load() {
    languages.readFile("res/lang/en.txt");
    Vector2f pos(Engine::getWindowSize());
    pos /= 2.f;
    _panel = Panel(pos, Vector2f(600.f, 200.f), "Anonymous.ttf");
    _panel.setPositionOfCentre(pos);
    _panel.setTextSize(40);
    _panel.setGUI(false);

    restartLevelbtn = Button(Vector2f(pos.x-100, pos.y+100), Vector2f(200.f, 35.f), languages.get("restart"));
    mainMenubtn = Button(Vector2f(pos.x-300, pos.y+100), Vector2f(200.f, 35.f), languages.get("main_menu"));
    setLoaded(true);
}

void GameOverScene::Update(const double& dt) {
    //for some reason if the text is set in load the score and time are always 0
    _panel.setTextLocalised(_message + "\nScore: " + std::to_string(score) + "\nTime: " + std::to_string(playerTime) + "s");

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
    score = 0;
    playerTime = 0;
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
  nextLevelbtn = Button(Vector2f(pos.x+100, pos.y+100), Vector2f(200.f, 35.f), languages.get("next_level"));
}
