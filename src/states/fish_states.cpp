#include "fish_states.h"
#include "../components/cmp_enemy_physics.h"
#include "../components/cmp_animated_sprite.h"
#include "../../engine/lib_tile_level_loader/LevelSystem.h"
#include "../Log.h"

using namespace sf;

// ----- SWIMMING STATE -----
void SwimmingState::execute(Entity* owner, double dt) noexcept {
    const auto pos = owner->getPosition();

    auto physics = owner->GetCompatibleComponent<PhysicsComponent>()[0];
    auto anim = owner->get_components<AnimatedSpriteComponent>()[0];

    auto mov = _direction * (float)(dt * 100);
    mov.x += _direction.x * 16.f;

    if(LevelSystem::getTileAt(pos + mov) == '2' || LevelSystem::getTileAt(pos + mov) == '0'){
        _direction *= -1.f;
    }

    physics->impulse(_direction * (float)(dt*100));
    anim->setFacingRight(_direction.x > 0);

    if(length(_player->getPosition() - pos) < 250.f) {
        auto sm = owner->get_components<StateMachineComponent>()[0];
        sm->changeState("jumping");
    }
}

// ----- JUMPING STATE -----
void JumpingState::execute(Entity* owner, double dt) noexcept {
    auto anim = owner->get_components<AnimatedSpriteComponent>()[0];
    anim->setFacingRight(!(_direction.x > 0));
    auto pos = owner->getPosition() + Vector2f(-33.f,0.f);
  auto pos2 = owner->getPosition() + Vector2f(0.f, -16.f);
    auto physics = owner->get_components<EnemyPhysicsComponent>()[0];
    if(ls::getTileAt(pos) == ls::baseTiles::DEADFALL || ls::getTileAt(pos) == '4' || ls::getTileAt(pos) == '6') {
        physics->setFriction(0.0f);
        physics->teleport(Vector2f(pos.x+30.f, pos.y - 2.0f));
        physics->impulse(Vector2f(.1f * _direction.x, -20.f));
        physics->setGravityScale(1);
        _direction.x *= -1.f;
    }
//  else if(ls::getTileAt(pos2) == '1' || ls::getTileAt(pos2) == '2', ls::getTileAt(pos2) == '3' , ls::getTileAt(pos2) == '7' ,
//            ls::getTileAt(pos2) == '8', ls::getTileAt(pos2) == '9'){
//      LOG(INFO)<<"jumping on ground";
//      physics->setFriction(0.f);
//      physics->teleport(Vector2f(pos2.x,pos2.y -1.f));
//      physics->impulse(Vector2f(-1.f * _direction.x, -10.f));
//      _direction *= -1.f;
//      physics->setGravityScale(1);
//    }

}

