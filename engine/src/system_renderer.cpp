#include "system_renderer.h"
#include "../../engine/src/engine.h"
#include <queue>

using namespace std;
using namespace sf;

static queue<const Drawable*> sprites;
static RenderWindow* rw;

void Renderer::initialise(sf::RenderWindow& r) { rw = &r; }

void Renderer::shutdown() {
  while (!sprites.empty())
    sprites.pop();
}

void Renderer::update(const double&) {}

void Renderer::render() {
  if (rw == nullptr) {
    throw("No render window set! ");
  }
  while (!sprites.empty()) {
    rw->draw(*sprites.front());
    sprites.pop();
  }
}

void Renderer::queue(const sf::Drawable* s) { 
  sprites.push(s); 
}

void Renderer::setView(sf::View &view) {
	rw->setView(view);
}

void Renderer::resetView() {
  auto v = rw->getDefaultView();
  rw->setView(v);
}
