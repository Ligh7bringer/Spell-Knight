#include "panel.h"
#include "../../engine/src/system_renderer.h"
#include "../../engine/src/system_resources.h"
#include <engine.h>
#include "../Log.h"

using namespace sf;

/*
* A GUI panel. Displays a rectangle with a string centered in it.
*/

//initialise everything needed
Panel::Panel(const Vector2f& size, const Vector2f& pos, const std::string& font) : _size(size), _position(pos) {
    _font = Resources::get<sf::Font>(font);
    _text.setFont(*_font);
    _text.setCharacterSize(32);
    _text.setFillColor(Color::Black);
    _text.setString("----");
    _text.setPosition(pos);
    _rect = RectangleShape(size);
    _rect.setFillColor(sf::Color(255,255,255,128));
}

void Panel::update(double dt) {
    //recalculate position of the panel so that it is always at the same position as the view moves
    auto pos = Engine::GetWindow().mapPixelToCoords(static_cast<Vector2i>(_position));

    //set the position
    _rect.setPosition(pos);
}

//render the panel and the text
void Panel::render() {
    Renderer::queue(&_rect);
    Renderer::queue(&_text);
}

//repositions the text so it is in the centre of the panel
void Panel::recentreText() {
    //get all needed dimensions and positions
    sf::Vector2f txtSize(_text.getLocalBounds().width, _text.getLocalBounds().height);
    sf::Vector2f containerSize(_rect.getLocalBounds().width, _rect.getLocalBounds().height);
    //global bounds contain transformations and translations which means the position will be correct
    //i.e. the text will always be in the view because the container is 
    sf::Vector2f containerPosition(_rect.getGlobalBounds().left, _rect.getGlobalBounds().top);

    //set position
    Vector2f newPos = (containerSize / 2.f) - (txtSize / 2.f) + containerPosition;
    newPos.y -= containerSize.y / 2.f;
    _text.setPosition(newPos);
}

//------ setters

//sets the text displayed in the panel
void Panel::setText(const std::string& text) {
    _renderString = text;
    _text.setString(_renderString);
    //make sure the text is centered
    recentreText();
}

//sets the colour of the panel
void Panel::setPanelColour(const Color& colour) {
    _rect.setFillColor(colour);
}

//sets the colour of the text
void Panel::setTextColour(const Color& colour) {
    _text.setFillColor(colour);
}
