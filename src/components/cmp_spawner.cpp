#include <texture_manager.h>
#include "cmp_spawner.h"
#include "cmp_physics.h"
#include "cmp_animated_sprite.h"
#include "../../engine/src/engine.h"
#include "../Log.h"
#include "cmp_cleanup.h"

/*
 * A boulder spawner component.
 */

SpawnerComponent::SpawnerComponent(Entity *p) : Component(p), _spawnTime(0.0f) {}

void SpawnerComponent::update(double dt) {
    //update timer
    _spawnTime -= dt;

    //if no more cooldown
    if(_spawnTime <= 0) {
        //create boulder
        auto boulder = _parent->scene->makeEntity();
        boulder->setPosition(_parent->getPosition());

        //add physics component
        auto physics = boulder->addComponent<PhysicsComponent>(true, sf::Vector2f(128.f, 128.f));
        physics->setRestitution(.4f);
        physics->setFriction(.0001f);
        physics->impulse(sf::Vector2f(-3.f, 0));
        //make it veeeeeeery heavy
        physics->setMass(1000000000.f);

        //add sprite
        auto anim = boulder->addComponent<AnimatedSpriteComponent>(sf::Vector2f(128.f, 128.f));
        anim->setSpritesheet(TextureManager::getTexture("boulder.png"));
        anim->setNumberOfFrames(1);
        //make it rotate
        anim->setRotation(-35.f);

        //make sure the boulder is deleted after a while
        boulder->addComponent<CleanUpComponent>(20.f);

        //reset timer
        _spawnTime = 3.5f;
    }
}