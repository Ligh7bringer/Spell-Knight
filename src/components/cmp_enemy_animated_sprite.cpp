#include "cmp_enemy_animated_sprite.h"
#include <SFML/Graphics.hpp>
#include "cmp_enemy_ai.h"
#include "../engine/lib_texture_manager/TextureManager.h"

using namespace std;
using namespace sf;

EnemyAnimatedSpriteComponent::EnemyAnimatedSpriteComponent(Entity *p, int width, int height) : AnimatedSpriteComponent(p, width, height) {
    //load spritesheet 
	_enemySpritesheet = TextureManager::getTexture("res/img/sheet_snake_walk.png");
    //set spritesheet
    setSpritesheet(_enemySpritesheet);
    setNumberOfFrames(5);
	//setSpriteSheetPadding(32);
    //set padding
    setFrameTime(0.15f);
}

void EnemyAnimatedSpriteComponent::update(double dt) {
    auto c = _parent->get_components<EnemyAIComponent>()[0];
    auto dir = c->getDirection();
	setFacingRight(dir.x > 0.0f ? false : true);

    //call super's update which will take care of everything else
    AnimatedSpriteComponent::update(dt);
}

//just use super's render
void EnemyAnimatedSpriteComponent::render() {
    AnimatedSpriteComponent::render();    
}