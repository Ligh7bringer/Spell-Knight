#include "cmp_enemy_health.h"
#include "cmp_animated_sprite.h"
#include "../Log.h"
#include "../config.h"

using namespace sf;

const int ALPHA = 180;
const Color Col_100_PERCENT = Color(51, 204, 51, ALPHA);
const Color COL_75_PERCENT = Color(255, 204, 0, ALPHA);
const Color COL_50_PERCENT = Color(255, 102, 0, ALPHA);
const Color COL_25_PERCENT = Color(255, 0, 0, ALPHA);

/*
* A component which allows enemies to have health so they don't necessarilly die after being shot once. 
* Also renders health bars above enemies.
*/

//initialise needed stuff
EnemyHealthComponent::EnemyHealthComponent(Entity* p, int health) : Component(p), _health(health), _maxHealth(health),
                                        _panel(Panel(_parent->getPosition(), Vector2f(50.f, 20.f))) {
    //create panel
    _panel.setTextSize(20);
    _panel.setPanelColour(Col_100_PERCENT);
    _panel.setGUI(false);

    //without an offset, the "health bar" is being rendered on top of the enemy.
    auto anim = _parent->get_components<AnimatedSpriteComponent>()[0];
    _offset = Vector2f(_panel.getBoundingBox().width, _panel.getBoundingBox().height);
    _offset.x = _offset.x / 2.f;
    _offset.y += anim->getSize().y / 2.f;
    _panelAlpha = 180;
}

void EnemyHealthComponent::update(double dt) {
    //update text to current health
    _panel.setText(Config::getLocalisedString("hp") + " " + std::to_string(_health));
    //update position
    _panel.setPosition(_parent->getPosition() - _offset);
    //update panel
    _panel.update(dt);
}

//render health bar
void EnemyHealthComponent::render() {
    _panel.render();
}

//reduces health by num
void EnemyHealthComponent::decreaseHealth(int num) {
    _health -= num;

    //if health is zero
    if(_health <= 0) {
        _health = 0;
        //enemy is dead, delete it
        _parent->setForDelete();
    }

    //if at 75% health, change the panel colour to yellow
    if(_health <= (int)(3.f/4.f * (float)_maxHealth)) {
        _panel.setPanelColour(COL_75_PERCENT);
    }   
    //if at 50% health, change the panel to orange
    if(_health <= _maxHealth / 2) {
        _panel.setPanelColour(COL_50_PERCENT);
    }  
    //if at 25% health, change the panel colour to red
    if(_health <= (int)(1.f/4.f * (float)_maxHealth)) {
        _panel.setPanelColour(COL_25_PERCENT);
    }
}

//increases health by num
void EnemyHealthComponent::increaseHealth(int num) {
    _health += num;
}