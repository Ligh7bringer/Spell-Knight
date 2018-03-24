#include "cmp_animated_sprite.h"
#include "system_renderer.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int prevRow;

//constructor, initialises default sprite size and default animation speed
AnimatedSpriteComponent::AnimatedSpriteComponent(Entity* p, int width, int height)
    : Component(p) {
        //width and height of the sprite
        _width = width;
        _height = height;
        //total accumulated time, used to tell when to switch to the next frame
        _totalTime = 0.0f;
        //the texture rect's width and height
        _currentFrame.width = _width;
        _currentFrame.height = _height;
        //current frame, default 0, 0
        _currentImage = Vector2u(0, 0);
        //default animation speed
        _frameTime = 0.2f;
        //this boolean is used to decide whether to flip the sprite or not
        _facingRight = true;
        //set this to the padding between rows in the spritesheet!!
        //all online spritesheet packers seem to add padding for some reason
        _spriteSheetPadding = 0;
		_currentRow = 0;
        _hurt = false;
        _hurtTimer = 1.0f;
        _numOfFrames = 1;
}

void AnimatedSpriteComponent::update(double dt) {
    //make sure we are at the right row in the spritesheet
    _currentImage.y = _currentRow;

    //reset to the 1st frame of new animation whenever animation is changed
    //fixes a number of problems, especially when the animations don't have the same number of frames
    //  if(_currentRow != prevRow) {
    //      _currentImage.x = 0;
    //     cout << _currentRow << ", " << _currentImage.y << endl;
    //  }

    //accumulate time
    _totalTime += dt;
    //if the time that has passed is greater than the animation speed (_frameTime)
    if (_totalTime > _frameTime) {
        //reset
        _totalTime -= _frameTime;
        //move on to next frame
        _currentImage.x++;
        //if there are no more frames
        if(_currentImage.x >= _numOfFrames) {
            //restart from the first frame
            _currentImage.x = 0;
        }
            
        //keep track of previous row
        prevRow = _currentImage.y;      
    }

    //if the sprite is supposed to be facing right
    if(_facingRight) {
        //set the texture rect's x to the correct x coordinate on the spritesheet
        _currentFrame.left = _currentImage.x * _width;
        //make sure the width is correct!!
        _currentFrame.width = abs(_currentFrame.width);
    } else { //if facing left
        //set the width to negative which should flip the sprite horizontally
        _currentFrame.left = (_currentImage.x + 1) * abs(_currentFrame.width);
        _currentFrame.width = -abs(_currentFrame.width);
    }
    
    //calculate spritesheet y coordinate, don't forget padding
    _currentFrame.top = _currentImage.y * _height + _spriteSheetPadding;

    //if entity is hurt start changing alpha
    if(_hurt) {
        _hurtTimer -= dt;
        static int alpha = 128;
        alpha -= 5;
        _sprite.setColor(Color(255, 255, 255, alpha));
    }

    //after the timer reaches 0
    //stop the hurt "animation"
    if(_hurt && _hurtTimer <= 0.f) {
        _hurt = false;
        _hurtTimer = 1.0f;
        _sprite.setColor(Color(255, 255, 255, 255));
    }

    //update sprite: set texture rect, update position and origin
    _sprite.setTextureRect(_currentFrame);
    _sprite.setPosition(_parent->getPosition());
    _sprite.setOrigin(_width/2, _height/2);
}

//render current sprite
void AnimatedSpriteComponent::render() {
    Renderer::queueAndOptimise(_sprite);
}

//sets the spritesheet, using the passed reference to a spritesheet
void AnimatedSpriteComponent::setSpritesheet(const sf::Texture& sh) {
    _spritesheet = sh;
    _sprite.setTexture(_spritesheet);
}

//sets animation speed
void AnimatedSpriteComponent::setFrameTime(float t) {
    _frameTime = t;
}

//sets number of frames the animation consists of
void AnimatedSpriteComponent::setNumberOfFrames(int num) {
    _numOfFrames = num;
}

//sets current row in the spritesheet 
void AnimatedSpriteComponent::setCurrentRow(int r) {
    _currentRow = r;
}

//sets padding
void AnimatedSpriteComponent::setSpriteSheetPadding(int padding) {
    _spriteSheetPadding = padding;
}

//sets whether the entity is facing right or not
void AnimatedSpriteComponent::setFacingRight(bool b) {
    _facingRight = b;
}

//sets the size of the sprite 
void AnimatedSpriteComponent::setSize(const Vector2f& size) {
    _width = size.x;
    _height = size.y;
    _currentFrame.left = _width;
    _currentFrame.top = _height;
}

Vector2f AnimatedSpriteComponent::getSize() const {
    return Vector2f(_currentFrame.width, _currentFrame.height);
}

//get or set if the entity is hurt
void AnimatedSpriteComponent::setHurt(bool h) {
    _hurt = h;
}

bool AnimatedSpriteComponent::isHurt() {
    return _hurt;
}

//returns whether the entity is facing right
bool AnimatedSpriteComponent::isFacingRight() const {
    return _facingRight;
}

int AnimatedSpriteComponent::getFrameCount() const {
    return _numOfFrames;
}

float AnimatedSpriteComponent::getFrameTime() const {
    return _frameTime;
}