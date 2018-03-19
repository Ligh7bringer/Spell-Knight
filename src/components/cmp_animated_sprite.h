#pragma once

#include "ecm.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


class AnimatedSpriteComponent : public Component {
protected:
  sf::Sprite _sprite;
  sf::Texture _spritesheet;
  sf::IntRect _currentFrame;
  sf::Vector2u _currentImage;
  float _totalTime;
  int _spriteSheetPadding;
  int _currentRow;
  float _frameTime;
  int _numOfFrames;
  int _width;
  int _height;
  bool _facingRight;
  bool _hurt;
  float _hurtTimer;

public:
  AnimatedSpriteComponent() = delete;

  explicit AnimatedSpriteComponent(Entity* p, int width, int height);
  void update(double dt) override;
  void render() override;

  void setSpritesheet(const sf::Texture& sh);
  void setFrameTime(float t);
  void setNumberOfFrames(int num);
  void setCurrentRow(int r);
  void setSpriteSheetPadding(int padding);
  void setFacingRight(bool b);
  void setSize(const sf::Vector2f& size);
  sf::Vector2f getSize() const;
  bool isFacingRight() const;

  void setHurt(bool h);
  bool isHurt();
};

