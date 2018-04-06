#pragma once

#include "cmp_sprite.h"
#include "ecm.h"
#include "system_physics.h"
#include <Box2D/Dynamics/b2Body.h>

class PhysicsComponent : public Component {
protected:
    b2Body* _body;
    const bool _dynamic;
    b2Fixture* _fixture;
    sf::Vector2f _size;

public:
    //constructor for creating static/dynamic bodies
    PhysicsComponent(Entity* p, bool dyn, const sf::Vector2f& size);
    //for creating a kinematic body
    PhysicsComponent(Entity* p, const sf::Vector2f& size);
    PhysicsComponent(Entity* p);

    b2Fixture* const getFixture() const;
    //bool isTouching(const PhysicsComponent& pc) const;
    bool isTouching(const PhysicsComponent& pc) const;
    std::vector<const b2Contact*> getTouching() const;
    const sf::Vector2f getVelocity() const;
    void setRestitution(float r);
    void setFriction(float r);
    void setMass(float m);
    void update(double dt) override;
    void render() override;
    void impulse(const sf::Vector2f& i);
    void applyForce(const sf::Vector2f& f);
    void dampen(const sf::Vector2f& s);
    void setVelocity(const sf::Vector2f& v);
    void teleport(const sf::Vector2f& v);
    void setLinearVelocity(const sf::Vector2f& move);
    void setGravityScale(int32 gs);
    b2ContactEdge* getContactList() const;
    const sf::Vector2f& getSize() const;
    const b2Vec2& getPosition() const;
    float32 getMass() const;
    ~PhysicsComponent() override;
};
