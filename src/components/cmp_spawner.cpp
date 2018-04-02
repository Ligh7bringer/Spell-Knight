#include <texture_manager.h>
#include "cmp_spawner.h"
#include "cmp_physics.h"
#include "cmp_animated_sprite.h"
#include "../../engine/src/engine.h"
#include "../Log.h"

SpawnerComponent::SpawnerComponent(Entity *p) : Component(p), _spawnTime(0.0f) {}

void SpawnerComponent::update(double dt) {
    _spawnTime -= dt;

    if(_spawnTime <= 0) {
        LOG(DEBUG) << "SPAWNING!";
        auto saw = _parent->scene->makeEntity();
        saw->setPosition(_parent->getPosition());
        saw->setRotation(45.f);
        auto physics = saw->addComponent<PhysicsComponent>(true, sf::Vector2f(128.f, 128.f));
        physics->setRestitution(.4f);
        physics->setFriction(.0001f);
        physics->impulse(sf::rotate(sf::Vector2f(-3.f, 0git), -_parent->getRotation()));
        physics->setMass(10000000.f);

        auto anim = saw->addComponent<AnimatedSpriteComponent>(sf::Vector2f(128.f, 128.f));
        anim->setSpritesheet(TextureManager::getTexture("saw.png"));
        anim->setNumberOfFrames(1);

        _spawnTime = 5.f;
    }
}