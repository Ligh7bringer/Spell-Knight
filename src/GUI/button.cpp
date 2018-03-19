#include "button.h"
#include "../../engine/src/system_renderer.h"
#include "../../engine/src/system_resources.h"
#include "../../engine/src/engine.h"
#include <iostream>

using namespace sf;

//constructor, sets size and text
Button::Button(const Vector2f& size, const std::string& text) {
    _size = size;
    _shape.setSize(size);
    _shape.setFillColor(Color::Green);
    _text.setString(text);
    //Font font;
    _font = Resources::get<sf::Font>("TravelingTypewriter.ttf");
    _text.setFont(*_font); 
    _clicked = false;
}

//sets position of the button
void Button::setPosition(const Vector2f& pos) {
    _shape.setPosition(pos);
    _text.setPosition(pos);
}

//checks for clicks or if the mouse is over the button
void Button::update(double dt) {
    auto mouseBox = getMouseRect(16, 16);
    auto btnRect = getBtnRect();

    if(mouseBox.intersects(btnRect)) {
        onHover();
    } else {
        reset();
    }

    if(mouseBox.intersects(btnRect) && Mouse::isButtonPressed(Mouse::Left)) {
        onClick();

        _clicked = true;
    } 
}

//renders the button and the text
void Button::render() {
    Renderer::queue(&_shape);
    Renderer::queue(&_text);
}

//called when the button is clicked, override to implement functionality
void Button::onClick() {
    _shape.setFillColor(Color::White);
}

//called when the mouse is on top the button
void Button::onHover() {
    _shape.setFillColor(Color::Red);
}

//called when the mouse is NOT on top of the button
void Button::reset() {
    _shape.setFillColor(Color::Green);
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

//returns the "hitbox" of the button
FloatRect Button::getBtnRect() {
    return FloatRect(_shape.getPosition().x, _shape.getPosition().y, _size.x, _size.y);
}

//returns whether the button has been clicked
bool Button::isClicked() const {
    return _clicked;
}