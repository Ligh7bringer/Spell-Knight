#pragma once
#include <SFML/Graphics.hpp>

namespace Renderer {
	void initiliase(sf::RenderWindow &);
	sf::RenderWindow &getWindow();

	void shutdown();
	void update(const double &);
	void queue(const sf::Drawable *s);
	void render();
}