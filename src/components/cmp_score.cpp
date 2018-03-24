#include "cmp_score.h"
#include <engine.h>

using namespace sf;

/*
* This component handles the player's score and renders the necessary GUI stuff to the screen.
*/

//load font, set up text and panel behind the text
PlayerScoreComponent::PlayerScoreComponent(Entity* p) : Component(p), _points(0) {
    _panel = Panel(Vector2f(500.f, 0), Vector2f(150.f, 32.f), "DoctorSoos.ttf");
    _panel.setPanelColour(Color(192, 192, 192, 128));
}


void PlayerScoreComponent::update(double dt) {
    _panel.setText("Score " + std::to_string(_points));
    _panel.update(dt);
}

//render the panel and the text
void PlayerScoreComponent::render() {
    _panel.render();
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