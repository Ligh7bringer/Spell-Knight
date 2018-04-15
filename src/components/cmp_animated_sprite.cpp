#include "cmp_animated_sprite.h"
#include "system_renderer.h"

using namespace sf;
using namespace std;

//constructor, initialises default sprite size and default animation speed
AnimatedSpriteComponent::AnimatedSpriteComponent(Entity* p, Vector2f size) : Component(p), _size(size), _rotation(0) {
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
    _done = false;
    //set origin
    auto origin = _size / 2.f;
    origin.x = floor(origin.x);
    origin.y = floor(origin.y);
    _sprite.setOrigin(origin);
}

void AnimatedSpriteComponent::update(double dt) {
    //make sure we're not locked in an animation
    if(!_locked) {
        //make sure we are at the right row in the spritesheet
        _currentImage.y = _currentRow;
        _done = false;
    }

    //accumulate time
    _totalTime += dt;
    //if the time that has passed is greater than the animation speed (_frameTime)
    if (_totalTime > _frameTime) {
        //reset
        _totalTime -= _frameTime;
        //move on to next frame
        _currentImage.x++;
        //if there are no more frames
		if (_currentImage.x >= _numOfFrames) {
			//unlock
			_locked = false;
			_done = true;
			//restart from the first frame
			_currentImage.x = 0;
		}
          //else{
           // _currentImage.x = _numOfFrames-1;
          //}
//          else{
//            if(_frameDecline ==_numOfFrames-1){
//              _currentImage.x= _numOfFrames-_frameDecline--;
//              _currentImage.x=_numOfFrames-_frameDecline--;
//            }

//          }


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

    if(_rotation != 0) {
        _sprite.rotate(_rotation * (float)dt);
    }
}

//render current sprite
void AnimatedSpriteComponent::render() {
    Renderer::queueAndOptimise(_sprite);
}

//makes sure the animation is played fully before playing any other animation
void AnimatedSpriteComponent::lockInAnimation(unsigned int row) {
    _currentImage.y = row;
    _currentImage.x = 0;
    _locked = true;
}

//sets the spritesheet, using the passed reference to a spritesheet
void AnimatedSpriteComponent::setSpritesheet(const sf::Texture& sh) {
    _spritesheet = sh;
    _sprite.setTexture(_spritesheet);
}

//sets animation speed
//t should be the time each frame is visible for
//so lower values = faster animation!
void AnimatedSpriteComponent::setFrameTime(float t) {
    _frameTime = t;
}

//sets number of frames the animation consists of
void AnimatedSpriteComponent::setNumberOfFrames(int num) {
    _numOfFrames = num;
}

//sets current row in the spritesheet 
void AnimatedSpriteComponent::setCurrentRow(int r) {
    //if changing to a new animation
    if(_currentRow != r) {
        _currentRow = r;
        //reset to first frame
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
    //update origin
    auto origin = _size / 2.f;
    origin.x = floor(origin.x);
    origin.y = floor(origin.y);
    _sprite.setOrigin(origin);
}

//returns the size of the sprite
const Vector2f& AnimatedSpriteComponent::getSize() const {
    return _size;
}

//get or set if the entity is hurt
void AnimatedSpriteComponent::setHurt(bool h) {
    _hurt = h;
}

//returns whether a hurt animation is being played
bool AnimatedSpriteComponent::isHurt() const {
    return _hurt;
}

//returns whether the entity is facing right
bool AnimatedSpriteComponent::isFacingRight() const {
    return _facingRight;
}

//returns the number of frames in current animation
int AnimatedSpriteComponent::getFrameCount() const {
    return _numOfFrames;
}

//returns the speed of the current animation
float AnimatedSpriteComponent::getFrameTime() const {
    return _frameTime;
}

bool AnimatedSpriteComponent::isDone() const {
    return _done;
}

const Sprite& AnimatedSpriteComponent::getSprite() const {
    return _sprite;
}

void AnimatedSpriteComponent::rotate(float deg) {
    _sprite.rotate(deg);
}

void AnimatedSpriteComponent::setRotation(float angle) {
    _rotation = angle;
}
