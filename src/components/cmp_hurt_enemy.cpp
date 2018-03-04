#include "cmp_hurt_enemy.h"
#include "cmp_player_bullet.h"
#include "cmp_bullet.h"
#include "cmp_physics.h"
#include <engine.h>
#include <iostream>

using namespace std;

//set parent and get the player
HurtEnemyComponent::HurtEnemyComponent(Entity* p) : Component(p), _player(_parent->scene->ents.find("player")[0]) {}

void HurtEnemyComponent::update(double dt) {
    //get the bullets from the player
    auto c = _player->get_components<PlayerBulletComponent>()[0];
    auto bullets = c->getBullets();
    //get compatible component because enemy physics component is a child of physics component!!
    const auto ppc = _parent->GetCompatibleComponent<PhysicsComponent>()[0];

    // //iterate over bullets
    // for(auto b : bullets) {
    //     if(!b->get_components<BulletComponent>()[0]->isExploded()) {
    //         //get each bullet's physics component
    //         const auto bpc = b->get_components<PhysicsComponent>()[0];  
    //         //if a bullet is colliding with the enemy
    //         if(ppc->isTouching(*bpc)) {
    //             //remove the bullet and the enemy
    //             bpc->setLinearVelocity(sf::Vector2f(0, 0));
    //             //c->removeBullet(b);
    //             _parent->setForDelete();
    //             //bpc->destroy();
    //             break;
    //         }
    //     }
    // }
}

void HurtEnemyComponent::render() {}