#ifndef GAMES_ENGINEERING_PARTICLES_H
#define GAMES_ENGINEERING_PARTICLES_H

#include <SFML/Graphics.hpp>
#include <deque>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
	enum Type
	{
		EXPLOSION,
		FLOATING,
		TRAIL
	};

	ParticleSystem() = delete;
	ParticleSystem(Type type, const sf::Texture& texture, float lifetime);

	void update(double dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void addParticle(const sf::Vector2f& pos);
	void setEmitter(const sf::Vector2f& pos);
	void emitParticles(double dt);
	void setColour(sf::Color c);
	void setEmissionRate(float rate);
	void setEmitterSize(const sf::Vector2f& size);

	void setLifetime(float _lifetime);

	void setEmitOffset(const sf::Vector2f& offset);

private:
	struct Particle
	{
		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::Color colour;
		float lifetime;
	};

	void computeVertices() const;
	void addVertex(
		float worldX, float worldY, float texCoordX, float texCoordY, const sf::Color& color) const;

	Type _type;
	std::deque<Particle> _particles;
	const sf::Texture& _texture;
	float _lifetime;
	sf::Vector2f _emitter;
	float _accumulatedTime;
	sf::Color _colour;
	float _emissionRate;
	sf::Vector2f _emitterSize;
	sf::Vector2f _offset;

	mutable sf::VertexArray _vertexArray;
	mutable bool _needsUpdate;
};

#endif //GAMES_ENGINEERING_PARTICLES_H
