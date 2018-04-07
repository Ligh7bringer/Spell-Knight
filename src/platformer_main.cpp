#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include "stdio.h"
#include "stdlib.h"

using namespace std;

MenuScene menu;
Level1Scene level1;
GameOverScene gameOver;

int main() {
  Engine::Start(1280, 720, "Spell Knight", (Scene*)&menu);
}