#pragma once

#include <SFML/Graphics.hpp>
//#include "cmp_sprite.h"

namespace Renderer
{
void initialise(sf::RenderWindow&);

void shutdown();

void update(const double&);

void queue(const sf::Drawable* s);

void render();

sf::RenderWindow& getWindow();

void setView(sf::View& view);

void resetView();

void queueAndOptimise(const sf::Sprite& sprite);

bool isInView(sf::FloatRect bounds);

}; // namespace Renderer
