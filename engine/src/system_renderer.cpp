#include "system_renderer.h"
#include "../../engine/src/engine.h"
#include "../../src/Log.h"
#include <queue>

using namespace std;
using namespace sf;

static queue<const Drawable*> sprites;
static queue<Sprite> _sprites;
static RenderWindow* rw;

void Renderer::initialise(sf::RenderWindow& r) { rw = &r; }

void Renderer::shutdown()
{
	while(!sprites.empty()) sprites.pop();

	while(!_sprites.empty()) _sprites.pop();
}

void Renderer::update(const double&) { }

void Renderer::render()
{
	// LOG(DEBUG) << sprites.size() << " non optimised sprites queued for rendering!";
	// LOG(DEBUG) << _sprites.size() << " optimised!";

	if(rw == nullptr)
	{
		throw("No render window set! ");
	}
	while(!sprites.empty())
	{
		rw->draw(*sprites.front());
		sprites.pop();
	}

	while(!_sprites.empty())
	{
		rw->draw(_sprites.front());
		_sprites.pop();
	}
}

void Renderer::queue(const sf::Drawable* s) { sprites.push(s); }

void Renderer::setView(sf::View& view) { rw->setView(view); }

void Renderer::resetView()
{
	auto v = rw->getDefaultView();
	rw->setView(v);
}

//use this method for frustum culling optimisation
void Renderer::queueAndOptimise(const Sprite& sprite)
{
	if(isInView(sprite.getGlobalBounds()))
	{
		_sprites.push(sprite);
	}
}

//checks whether a sprite is within the view
//used to tell whether to render something or not
bool Renderer::isInView(sf::FloatRect bounds)
{
	auto view = rw->getView();
	IntRect viewRect;
	viewRect.width = view.getSize().x;
	viewRect.height = view.getSize().y;
	viewRect.left = view.getCenter().x - view.getSize().x / 2;
	viewRect.top = view.getCenter().y - view.getSize().y / 2;

	auto spriteBounds = static_cast<IntRect>(bounds);
	return spriteBounds.intersects(viewRect);
}
