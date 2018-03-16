#include "cmp_pickup.h"
#include "cmp_score.h"

/*
* Component which allows pickups to be picked up and increase the player's score.
*/

void PickUpComponent::update(double dt) {
    //get player
    if(auto player = _player.lock()) {
        //check distance is less than 25
        //this is fine for now but might need to use box2d for collisions later
        if(sf::length(player->getPosition() - _parent->getPosition()) < 25.0f) {
            //delete pick up
            _parent->setForDelete();
            //get score component and increase score
            auto score = player->get_components<PlayerScoreComponent>()[0];
            score->increasePoints(10);
        }
    }
}

//nothing to render
void PickUpComponent::render() {}

//the constructor gets a pointer to the player
PickUpComponent::PickUpComponent(Entity* p) : Component(p), _player(_parent->scene->ents.find("player")[0]) {}