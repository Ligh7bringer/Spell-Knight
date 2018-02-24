#include "cmp_animated_sprite.h"
#include "system_renderer.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

//constructor, initialises default sprite size and default animation speed
AnimatedSpriteComponent::AnimatedSpriteComponent(Entity* p, int width, int height)
    : Component(p) {
        _width = width;
        _height = height;
        _currentFrame = IntRect(0, 0, _width, _height);
        _frameTime = 0.2f;
        _numOfFrames = 5;
}

void AnimatedSpriteComponent::update(double dt) {
    //go to next frame
    if (_clock.getElapsedTime().asSeconds() > 0.2f) {
        _currentFrame.left += 64;
        //if there are no more frames
        if(_currentFrame.left >= _numOfFrames * 64) {
            //start from the frist frame
            _currentFrame.left = 0;
        }
        _clock.restart();
    }

    //update sprite
    _sprite.setTexture(_spritesheet);
    _sprite.setTextureRect(_currentFrame);
    _sprite.setPosition(_parent->getPosition());
    _sprite.setOrigin(_width/2, _height/2);
}

//render current sprite
void AnimatedSpriteComponent::render() {
    Renderer::queue(&_sprite);
}

//set the sprite sheet for the animation
void AnimatedSpriteComponent::setSpritesheet(string path) {
    if(!_spritesheet.loadFromFile(path)) {
        cout << "Couldn't load component's spritesheet!";
    }
}

//set animation speed
void AnimatedSpriteComponent::setFrameTime(float t) {
    _frameTime = t;
}

//set number of frames the animation consists of
void AnimatedSpriteComponent::setNumberOfFrames(int num) {
    _numOfFrames = num;
}