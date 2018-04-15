#include <audio_manager.h>
#include "cmp_teleport.h"
#include "../game.h"

/*
 * Component which allows the player to be teleported
 */

void TeleportComponent::update(double dt){
  //get the player
  if(auto player = _player.lock()){
    //check the distance is less than 30
    if(sf::length(player->getPosition() - _parent->getPosition()) < 30.0f){
      //kill the player
      player->setAlive(false);
    }
  }
}

//nothing to render
void TeleportComponent::render() {}

//constructor gets the player
TeleportComponent::TeleportComponent(Entity *p) : Component(p), _player(_parent->scene->ents.find("player")[0]) {}