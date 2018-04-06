#include "cmp_physics.h"
#include "cmp_animated_sprite.h"

using namespace std;
using namespace sf;

using namespace Physics;

void PhysicsComponent::update(double dt) {
  _parent->setPosition(invert_height(bv2_to_sv2(_body->GetPosition())));
  _parent->setRotation((180 / b2_pi) * _body->GetAngle());
}

PhysicsComponent::PhysicsComponent(Entity* p, bool dyn,
                                   const Vector2f& size)
    : Component(p), _dynamic(dyn) {
  
  _size = size;

  b2BodyDef BodyDef;
  // Is Dynamic(moving), or static(Stationary)
  BodyDef.type = _dynamic ? b2_dynamicBody : b2_staticBody;
  BodyDef.position = sv2_to_bv2(invert_height(p->getPosition()));

  // Create the body
  _body = Physics::GetWorld()->CreateBody(&BodyDef);
  _body->SetActive(true);
  {
    // Create the fixture shape
    b2PolygonShape Shape;
    // SetAsBox box takes HALF-Widths!
    Shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
    b2FixtureDef FixtureDef;
    // Fixture properties
    // FixtureDef.density = _dynamic ? 10.f : 0.f;
    FixtureDef.friction = _dynamic ? 0.1f : 0.8f;
    FixtureDef.restitution = .2;
    FixtureDef.shape = &Shape;
    // Add to body
    _fixture = _body->CreateFixture(&FixtureDef);
    //_fixture->SetRestitution(.9)
    FixtureDef.restitution = .2;
  }

  // An ideal Pod/capusle shape should be used for hte player,
  // this isn't built into B2d, but we can combine two shapes to do so.
  // This would allwo the player to go up steps
  /*
    BodyDef.bullet = true;
    b2PolygonShape shape1;
    shape1.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
    {
      b2PolygonShape poly ;
      poly.SetAsBox(0.45f, 1.4f);
      b2FixtureDef FixtureDefPoly;

      FixtureDefPoly.shape = &poly;
      _body->CreateFixture(&FixtureDefPoly);

    }
    {
      b2CircleShape circle;
      circle.m_radius = 0.45f;
      circle.m_p.Set(0, -1.4f);
      b2FixtureDef FixtureDefCircle;
      FixtureDefCircle.shape = &circle;
      _body->CreateFixture(&FixtureDefCircle);
    }
  */
}

//creates a kinematic body! 
PhysicsComponent::PhysicsComponent(Entity* p, const sf::Vector2f& size) : Component(p), _size(size), _dynamic(false) {
  b2BodyDef BodyDef;
  // kinematic bodies are not affected by forces so they are perfect for moving platforms (almost)
  BodyDef.type = b2_kinematicBody;
  BodyDef.position = sv2_to_bv2(invert_height(p->getPosition()));

  // Create the body
  _body = Physics::GetWorld()->CreateBody(&BodyDef);
  _body->SetActive(true);
  {
    // Create the fixture shape
    b2PolygonShape Shape;
    // SetAsBox box takes HALF-Widths!
    Shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
    b2FixtureDef FixtureDef;
    // Fixture properties
    FixtureDef.friction = 0.1f;
    FixtureDef.restitution = 0;
    FixtureDef.shape = &Shape;
    // Add to body
    _fixture = _body->CreateFixture(&FixtureDef);
  }
}

//creates a triangular body
PhysicsComponent::PhysicsComponent(Entity *p) : Component(p), _dynamic(false) {
    //create body def
    b2BodyDef bodyDef;
    //set dynamic/static
    bodyDef.type = b2_staticBody;
    bodyDef.position = sv2_to_bv2(invert_height(p->getPosition()));
    //create body
    _body = Physics::GetWorld()->CreateBody(&bodyDef);
    _body->SetActive(true);

    //create a triangular shape
    //with some nice hardcoded values
    b2Vec2 vertices[3];
    vertices[0].Set(-0.2f, 0.0f);
    vertices[1].Set(0.5f, 0.0f);
    vertices[2].Set(0.4f, 1.0f);
    int32 count = 3;
    b2PolygonShape polygon;
    polygon.Set(vertices, count);

    //create fixture def
    b2FixtureDef fixtureDef;
    fixtureDef.friction = 0.1f;
    fixtureDef.restitution = 0;
    fixtureDef.shape = &polygon;

    //create fixture
    _fixture = _body->CreateFixture(&fixtureDef);
}

void PhysicsComponent::setFriction(float r) { _fixture->SetFriction(r); }

void PhysicsComponent::setMass(float m) { _fixture->SetDensity(m); }

void PhysicsComponent::teleport(const sf::Vector2f& v) {
  _body->SetTransform(sv2_to_bv2(invert_height(v)), 0.0f);
}

const sf::Vector2f PhysicsComponent::getVelocity() const {
  return bv2_to_sv2(_body->GetLinearVelocity(), true);
}
void PhysicsComponent::setVelocity(const sf::Vector2f& v) {
  _body->SetLinearVelocity(sv2_to_bv2(v, true));
}

b2Fixture* const PhysicsComponent::getFixture() const { return _fixture; }

PhysicsComponent::~PhysicsComponent() {
  auto a = Physics::GetWorld();
  _body->SetActive(false);
  Physics::GetWorld()->DestroyBody(_body);
  // delete _body;
  _body = nullptr;
}

void PhysicsComponent::render() {}

void PhysicsComponent::impulse(const sf::Vector2f& i) {
  auto a = b2Vec2(i.x, i.y * -1.0f);
  _body->ApplyLinearImpulseToCenter(a, true);
}

void PhysicsComponent::dampen(const sf::Vector2f& i) {
  auto vel = _body->GetLinearVelocity();
  vel.x *= i.x;
  vel.y *= i.y;
  _body->SetLinearVelocity(vel);
}

//bool PhysicsComponent::isTouching(const PhysicsComponent& pc) const {
  //b2Contact* bc;
  //return isTouching(pc, bc);
//}

bool PhysicsComponent::isTouching(const PhysicsComponent& pc) const {
  const auto _otherFixture = pc.getFixture();
  //instead of using a list of all the contacts in the world, it would be better to use a list of contacts 
  //for the current entity. Seems to fix the segfault problem
  const auto contactList = getTouching();
  for (int32 i = 0; i < contactList.size(); i++) {
    const auto& contact = (contactList[i]);
    //the bodies need to be compared here, not the fixtures!
    if (contact->IsTouching() &&
       ((contact->GetFixtureA()->GetBody() == _fixture->GetBody() &&
        contact->GetFixtureB()->GetBody() == _otherFixture->GetBody()) ||
       (contact->GetFixtureA()->GetBody() == _otherFixture->GetBody() &&
        contact->GetFixtureB()->GetBody() == _fixture->GetBody()))) {

      //bc = &contact;
      return true;
    }
  }
  return false;
}

std::vector<const b2Contact*> PhysicsComponent::getTouching() const {
  std::vector<const b2Contact*> ret;

  b2ContactEdge* edge = _body->GetContactList();
  while (edge != NULL) {
    const b2Contact* contact = edge->contact;
    if (contact->IsTouching()) {
      ret.push_back(contact);
    }
    edge = edge->next;
  }

  return ret;
}

void PhysicsComponent::setRestitution(float r) {
  _fixture->SetRestitution(r);
}

void PhysicsComponent::setLinearVelocity(const Vector2f& move) {
  _body->SetLinearVelocity(b2Vec2(move.x, move.y * -1.f));
}

void PhysicsComponent::setGravityScale(int32 gs) {
  _body->SetGravityScale(gs);
}

b2ContactEdge* PhysicsComponent::getContactList() const {
  return _body->GetContactList();
}

const Vector2f& PhysicsComponent::getSize() const {
  return _size;
}

const b2Vec2& PhysicsComponent::getPosition() const {
  return _body->GetPosition();
}

float32 PhysicsComponent::getMass() const {
  return _body->GetMass();
}

void PhysicsComponent::applyForce(const Vector2f& f) {
  auto a = b2Vec2(f.x, f.y * -1.0f);
  _body->ApplyForceToCenter(a, true);
}


