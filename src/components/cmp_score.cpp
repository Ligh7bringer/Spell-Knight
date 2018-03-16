#include "cmp_score.h"
#include <iostream>
#include "../../engine/src/system_resources.h"
#include <engine.h>
#include "../../engine/src/system_renderer.h"

using namespace sf;

/*
* This component handles the player's score and renders the necessary GUI stuff to the screen.
*/

//load font, set up text and panel behind the text
PlayerScoreComponent::PlayerScoreComponent(Entity* p) : Component(p), _points(0), _panel(RectangleShape(Vector2f(100.f, 34.f))) {
    _font = Resources::get<sf::Font>("DoctorSoos.ttf");
    _panel.setFillColor(sf::Color(255,255,255,128));
    _text.setFont(*_font);
    _text.setCharacterSize(32);
    _text.setFillColor(Color::Black);
}


void PlayerScoreComponent::update(double dt) {
    //convert world coordinates to view coordinates
     auto pos = Engine::GetWindow().mapPixelToCoords(Vector2i(500, 0));
     //set positions
    _panel.setPosition(pos);

    //update text
    _text.setPosition(_panel.getPosition());
    _text.setString("Score " + std::to_string(_points));
}

//render the panel and the text
void PlayerScoreComponent::render() {
    Renderer::queue(&_panel);
    Renderer::queue(&_text);
}

//increases points 
void PlayerScoreComponent::increasePoints(int num) {
    _points += num;
}

//decreases points and makes sure they are not lower than 0
void PlayerScoreComponent::decreasePoints(int num) {
    _points -= num;
    if(_points < 0) {
        _points = 0;
    }
}

//returns current points
int PlayerScoreComponent::getPoints() const {
    return _points;
}