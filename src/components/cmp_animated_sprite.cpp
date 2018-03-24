#include "cmp_animated_sprite.h"
#include "system_renderer.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int prevRow;

//constructor, initialises default sprite size and default animation speed
AnimatedSpriteComponent::AnimatedSpriteComponent(Entity* p, Vector2f size) : Component(p), _size(size) {
        //total accumulated time, used to tell when to switch to the next frame
        _totalTime = 0.0f;
        //the texture rect's width and height
        _currentFrame.width = _size.x;
        _currentFrame.height = _size.y;
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
        _currentFrame.left = _currentImage.x * _size.x;
        //make sure the width is correct!!
        _currentFrame.width = abs(_currentFrame.width);
    } else { //if facing left
        //set the width to negative which should flip the sprite horizontally
        _currentFrame.left = (_currentImage.x + 1) * abs(_currentFrame.width);
        _currentFrame.width = -abs(_currentFrame.width);
    }
    
    //calculate spritesheet y coordinate, don't forget padding
    _currentFrame.top = _currentImage.y * _size.y + _spriteSheetPadding;

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
    auto origin = _size / 2.f;
    origin.x = floor(origin.x);
    origin.y = floor(origin.y);
    _sprite.setOrigin(origin);
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
    if(_currentRow != r) {
        _currentRow = r;    
        _currentImage.x = 0;
    }
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
    _size = size;
    _currentFrame.left = _size.x;
    _currentFrame.top = _size.y;
}

const Vector2f& AnimatedSpriteComponent::getSize() const {
    return _size;
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
