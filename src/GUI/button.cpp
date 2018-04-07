#include <settings_parser.h>
#include "button.h"
#include "../../engine/src/system_renderer.h"
#include "../../engine/src/engine.h"

using namespace sf;

//constructor, sets size and text
Button::Button(const Vector2f& pos, const Vector2f& size, const std::string& text) : _check(true), _timer(0.2f) {
    _panel = Panel(pos, size, "Anonymous.ttf");
    _panel.setTextLocalised(text);
    _panel.setTextSize(30);
    _panel.setGUI(false);
    _panel.setBorder(2, Color::Magenta);
    _position = pos;
    _clicked = false;
}

//sets position of the button
void Button::setPosition(const Vector2f& pos) {
    _panel.setPositionOfCentre(pos);
    _position = pos;
}

//checks for clicks or if the mouse is over the button
void Button::update(double dt) {
    _clicked = false;

    auto mouseBox = getMouseRect(16, 16);
    auto btnRect = _panel.getBoundingBox();

    if(mouseBox.intersects(btnRect)) {
        onHover();
    } else {
        reset();
    }

    if(mouseBox.intersects(btnRect) && Mouse::isButtonPressed(Mouse::Left) && _check) {
        onClick();
        _clicked = true;
        _check = false;
    }
    if(!_check) {
        _timer -=dt;
    }
    if(_timer <= 0.0f) {
        _timer = 0.2f;
        _check = true;
    }
}

//renders the button and the text
void Button::render() {
    _panel.render();
}

//called when the button is clicked
void Button::onClick() {
    _panel.setPanelColour(Color::White);
}

//called when the mouse is on top the button
void Button::onHover() {
    _panel.setPanelColour(Color::Red);
}

//called when the mouse is NOT on top of the button
void Button::reset() {
    _panel.setPanelColour(Color::Green);
}

//returns the "hitbox" of the mouse
FloatRect Button::getMouseRect(int width, int height) {
    FloatRect mouseBox;
    mouseBox.width = width;
    mouseBox.height = height;
    mouseBox.left = Mouse::getPosition(Engine::GetWindow()).x;
    mouseBox.top = Mouse::getPosition(Engine::GetWindow()).y;

    return mouseBox;
}

//returns whether the button has been clicked
bool Button::isClicked() const {
    return _clicked;
}

const sf::Vector2f &Button::getPosition() {
    return _position;
}
