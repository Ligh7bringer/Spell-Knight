#include "cmp_hurt_enemy.h"
#include "cmp_player_bullet.h"
#include <engine.h>
#include <iostream>

using namespace std;

HurtEnemyComponent::HurtEnemyComponent(Entity* p) : Component(p), _player(_parent->scene->ents.find("player")[0]) {}

void HurtEnemyComponent::update(double dt) {
    auto c = _player->get_components<PlayerBulletComponent>()[0];
    auto bullets = c->getBullets();
    for(auto b : bullets) {
        //cout << length(b->getPosition() - _parent->getPosition()) << endl;
        if((length(b->getPosition() - _parent->getPosition()) < 40.0)) {
            _parent->setForDelete();
            c->removeBullet(b);
            break;
        }
    }
}

void HurtEnemyComponent::render() {}