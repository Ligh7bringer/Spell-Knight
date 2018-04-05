#include <audio_manager.h>
#include "cmp_pickup.h"
#include "cmp_score.h"
#include "cmp_player_attack.h"

/*
* Component which allows pickups to be picked up and increase the player's score.
*/

void PickUpComponent::update(double dt) {
    //get player
    if(auto player = _player.lock()) {
        //check distance is less than 25
        //this is fine for now but might need to use box2d for collisions later
        if(sf::length(player->getPosition() - _parent->getPosition()) < 25.0f) {
            //get score component and increase score
            auto score = player->get_components<PlayerScoreComponent>()[0];
            score->increasePoints(_points);
            auto attack = player->get_components<PlayerAttackComponent>()[0];
            AudioManager::playSound("collect.wav");
            //delete
            _parent->setForDelete();
        }
    }
}

//nothing to render
void PickUpComponent::render() {}

//the constructor gets a pointer to the player
PickUpComponent::PickUpComponent(Entity* p, unsigned int points) : Component(p), _player(_parent->scene->ents.find("player")[0]), _points(points) {}