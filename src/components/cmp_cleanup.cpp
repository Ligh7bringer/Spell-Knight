#include "cmp_cleanup.h"
#include "../Log.h"

/*
 * Simple component which deletes enemies after a while.
 */

CleanUpComponent::CleanUpComponent(Entity* p, float lifeTime) : Component(p), _lifeTime(lifeTime) {}

void CleanUpComponent::update(double dt) {
    _lifeTime -= dt;

    if(_lifeTime <= 0) {
        _parent->setForDelete();
        //LOG(DEBUG) << "despawning";
    }
}
