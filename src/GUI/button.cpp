#include <settings_parser.h>
#include "button.h"
#include "../../engine/src/system_renderer.h"
#include "../../engine/src/engine.h"

using namespace sf;

//constructor, sets size and text
Button::Button(const Vector2f& pos, const Vector2f& size, const std::string& text) {
    _panel = Panel(pos, size, "Anonymous.ttf");
    _panel.setTextLocalised(text);
    _panel.setTextSize(30);
    _panel.setGUI(false);
    _clicked = false;
}

//sets position of the button
void Button::setPosition(const Vector2f& pos) {
    _panel.setPosition(pos);
}

//checks for clicks or if the mouse is over the button
void Button::update(double dt) {
    auto mouseBox = getMouseRect(16, 16);
    auto btnRect = _panel.getBoundingBox();

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