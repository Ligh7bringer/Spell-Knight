#include "slime_states.h"
#include "../components/cmp_enemy_physics.h"
#include "../components/cmp_animated_sprite.h"
#include "../../engine/lib_tile_level_loader/LevelSystem.h"

/*
* Behaviour of the slime enemy.
*/

using namespace sf;

// ----- ROAMING STATE -----
void RoamingState::execute(Entity* owner, double dt) noexcept {
    auto physics = owner->GetCompatibleComponent<PhysicsComponent>()[0];
    auto anim = owner->get_components<AnimatedSpriteComponent>()[0];

    const auto pos = owner->getPosition() ;
    auto mov = _direction * (float)(dt * 100);
    mov.x += _direction.x * 16.f;

    if(LevelSystem::getTileAt(pos + mov) == '2' || LevelSystem::getTileAt(pos + mov) == '0'){
        _direction *= -1.f;
    }

    physics->impulse(_direction * (float)(dt*100));
    anim->setFacingRight(_direction.x > 0);
}