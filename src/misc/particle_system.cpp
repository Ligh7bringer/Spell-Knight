#include "particle_system.h"
#include "../Log.h"
#include <cmath>

/*
 * Greatly improved particle system.
 */

ParticleSystem::ParticleSystem(Type type, const sf::Texture& texture, float lifetime)
	: _texture(texture)
	, _lifetime(lifetime)
	, _accumulatedTime(0)
	, _vertexArray(sf::Quads, 1000)
	, _type(type)
	, _colour(sf::Color::Cyan)
	, _emissionRate(30.f)
	, _emitterSize(sf::Vector2f(64.f, 64.f))
	, _offset(sf::Vector2f(0, 0))
{ }
//adds a particle
void ParticleSystem::addParticle(const sf::Vector2f& pos)
{
	//create a particle
	Particle particle;
	particle.position = _emitter;
	particle.colour = _colour;
	particle.lifetime = _lifetime;

	//set velocity and lifetime depending on effect type
	if(_type == Type::FLOATING)
	{
		particle.position = sf::Vector2f(rand() % static_cast<int>(_emitterSize.x) + pos.x -
											 _emitterSize.x / 2.f + _offset.x,
										 pos.y + _emitterSize.y / 2.f + _offset.y);
		particle.velocity = sf::Vector2f(0, -50.0f);
	}
	if(_type == Type::EXPLOSION)
	{
		float angle = (std::rand() % 360) * 3.14f / 180.f;
		float speed = (std::rand() % 50) + 50.f;
		particle.velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	}
	if(_type == Type::TRAIL)
	{
		particle.velocity = sf::Vector2f(0.0f, 0.0f);
	}

	//add to the list
	_particles.push_back(particle);
}

//update particles
void ParticleSystem::update(double dt)
{
	//check the particle in the front of the deque and remove it if its life is over
	while(!_particles.empty() && _particles.front().lifetime < 0.f) _particles.pop_front();

	//update lifetime and positions of all particles
	for(Particle& particle : _particles)
	{
		particle.lifetime -= dt;
		particle.position += particle.velocity * static_cast<float>(dt);
	}

	//optimisations
	_needsUpdate = true;
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(_needsUpdate)
	{
		//recalculate vertices
		computeVertices();
		_needsUpdate = false;
	}

	//set texture
	states.texture = &_texture;

	//update transform
	states.transform *= getTransform();

	//draw
	target.draw(_vertexArray, states);
}

void ParticleSystem::computeVertices() const
{
	//get size and half size of texture
	sf::Vector2f size(_texture.getSize());
	sf::Vector2f half = size / 2.f;

	//clear vertex array
	_vertexArray.clear();

	for(const Particle& particle : _particles)
	{
		sf::Vector2f pos = particle.position;
		sf::Color c = particle.colour;

		//set alpha depending on lifetime
		float ratio = particle.lifetime / _lifetime;
		c.a = static_cast<sf::Uint8>(255 * std::max(ratio, 0.f));

		//add new quad with appropriate texture coordinates and position
		addVertex(pos.x - half.x, pos.y - half.y, 0.f, 0.f, c);
		addVertex(pos.x + half.x, pos.y - half.y, size.x, 0.f, c);
		addVertex(pos.x + half.x, pos.y + half.y, size.x, size.y, c);
		addVertex(pos.x - half.x, pos.y + half.y, 0.f, size.y, c);
	}
}

//adds a vertex to the vertex array
void ParticleSystem::addVertex(
	float worldX, float worldY, float texCoordX, float texCoordY, const sf::Color& color) const
{
	sf::Vertex vertex;
	vertex.position = sf::Vector2f(worldX, worldY);
	vertex.texCoords = sf::Vector2f(texCoordX, texCoordY);
	vertex.color = color;
	_vertexArray.append(vertex);
}

//sets the position from which particles are emitted
void ParticleSystem::setEmitter(const sf::Vector2f& pos) { _emitter = pos; }

//creates particles
void ParticleSystem::emitParticles(double dt)
{
	//interval of emission
	const float interval = 1.f / _emissionRate;

	//accumulate time
	_accumulatedTime += dt;
	//if enough time has passed
	while(_accumulatedTime > interval)
	{
		//reset timer
		_accumulatedTime -= interval;
		//create a particle
		addParticle(_emitter);
	}
}

void ParticleSystem::setColour(sf::Color c) { _colour = c; }

void ParticleSystem::setEmissionRate(float rate) { _emissionRate = rate; }

void ParticleSystem::setEmitterSize(const sf::Vector2f& size) { _emitterSize = size; }

void ParticleSystem::setEmitOffset(const sf::Vector2f& offset) { _offset = offset; }

void ParticleSystem::setLifetime(float lifetime) { _lifetime = lifetime; }
