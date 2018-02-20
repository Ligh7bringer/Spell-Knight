#pragma once
#include "scene.h"
#include <SFML/Graphics.hpp>

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

//Menu scene
class MenuScene : public Scene {
public: 
    MenuScene();
    void Update(double dt) override;
    void Render() override;
    void Load() override;
};

//Game Scene
class GameScene : public Scene {
private:
    sf::Text text;
    void Respawn();

public: 
    GameScene();
    void Update(double dt) override;
    void Render() override;
    void Load() override;
};