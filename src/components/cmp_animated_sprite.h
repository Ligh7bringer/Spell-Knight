#pragma once

#include "ecm.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


class AnimatedSpriteComponent : public Component {
protected:
  //std::shared_ptr<sf::Sprite> _sprite;
  //std::shared_ptr<sf::Texture> _spritesheet;
  sf::Sprite _sprite;
  sf::Texture _spritesheet;
  sf::IntRect _currentFrame;
  sf::Vector2u _currentImage;
  int _spriteSheetPadding;
  int _currentRow;
  float _totalTime;
  float _frameTime;
  int _numOfFrames;
  int _width;
  int _height;
  bool _facingRight;

public:
  AnimatedSpriteComponent() = delete;

  explicit AnimatedSpriteComponent(Entity* p, int width, int height);
  void update(double dt) override;
  void render() override;

  void setSpritesheet(std::string path);
  void setSpritesheet(sf::Texture& sh);
  void setFrameTime(float t);
  void setNumberOfFrames(int num);
  void setCurrentRow(int r);
  void setSpriteSheetPadding(int padding);
  void setFacingRight(bool b);
};

