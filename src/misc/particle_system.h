#include <SFML/Graphics.hpp>
#include "../../engine/lib_texture_manager/TextureManager.h"
#include <cmath>
#include <memory>
#include "../Log.h"

/*
* This class allows the creation of particle systems. Should be very efficient as the particles are stored in a vertex array.
*/

class ParticleSystem : public sf::Drawable, public sf::Transformable {
private:
    //this methoud shouldn't be called, instead use window.draw(particles)
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // no texture (yet?)
        //states.texture = &tex;

        // draw the vertex array
        target.draw(_vertices, states);
    }

    //defines a single particle
    struct Particle {
        sf::Vector2f velocity;
        float lifetime;
    };

    //resets a particle after its life is over
    void resetParticle(std::size_t index) {
        // give a random velocity and lifetime to the particle
        float angle = (std::rand() % 360) * 3.14f / 180.f;
        float speed = (std::rand() % 50) + 50.f;
        _particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        _particles[index].lifetime = ((float)(std::rand() % 2000) + 1000) / 1000.f;
       
        // reset the position of the corresponding vertex
        _vertices[index].position = _emitter;
    }

    //vector to store the particles
    std::vector<Particle> _particles;
    //vertex array to store the points
    sf::VertexArray _vertices;
    //how long the particle should be visible for
    float _lifetime;
    //starting position of the particles
    sf::Vector2f _emitter;
    //colour of particles
    sf::Color _colour;
    //should the particles fade away over time
    bool _fadeAway;

public:
    ParticleSystem() = default;
    //initialise everything
    explicit ParticleSystem(unsigned int count) :
    _particles(count), 
    _vertices(sf::Points, count),
    _lifetime(3.f),
    _emitter(sf::Vector2f(0, 0)),
    _colour(sf::Color::White),
    _fadeAway(true)
    {}

    //sets the starting position of the particles
    void setEmitter(const sf::Vector2f& pos) {
        _emitter = pos;
    }

    void setParticleColor(sf::Color c) {
        _colour = c;
    }

    void fadeAway(bool b) {
        _fadeAway = b;
    }

    //update particles
    void update(double dt) {
        //iterate over particles
        for(std::size_t i = 0; i < _particles.size(); ++i) {
            //get particle
            Particle& p = _particles[i];
            //reduce lifetime by delta time
            p.lifetime -= dt;

            //if its life is over
            if(p.lifetime <= 0) {
                //reset it
                resetParticle(i);
            }

            //move it 
            _vertices[i].position += p.velocity * (float)dt;
            
            if(!_fadeAway) {
                _vertices[i].color = _colour;
            } else {
                //update the alpha according to lifetime
                float ratio = p.lifetime / _lifetime;
                _vertices[i].color = sf::Color(_colour.r, _colour.g, _colour.b, static_cast<sf::Uint8>(ratio * 255));
            }
        }
    }

    ~ParticleSystem() = default;    
};