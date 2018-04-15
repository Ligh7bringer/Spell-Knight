#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include "stdio.h"
#include "stdlib.h"
#include "config.h"
#include "Log.h"

using namespace std;

MenuScene menu;
Level1Scene level1;
GameOverScene gameOver;
OptionsScene options;


int main() {
  LOG(DEBUG) << Config::getDefaultFont();
  Config::firstRun();
  auto width_str = Config::getSetting("width");
  auto height_str = Config::getSetting("height");
  auto width = stoi(width_str);
  auto height = stoi(height_str);
  Engine::Start(width, height, "Spell Knight", (Scene*)&menu);
}