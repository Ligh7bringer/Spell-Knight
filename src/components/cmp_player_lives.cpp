#include "cmp_player_lives.h"
#include "../../engine/src/system_renderer.h"
#include "../../engine/lib_texture_manager/TextureManager.h"
#include "../../engine/src/system_resources.h"
#include <engine.h>

using namespace sf;

PlayerLivesComponent::PlayerLivesComponent(Entity* p, int maxLives) : Component(p), _maxLives(maxLives), _lives(_maxLives) {
    _panel = RectangleShape(Vector2f(100.f, 34.f));
    _panel.setFillColor(sf::Color(255,255,255,128));
    _font = Resources::get<sf::Font>("DoctorSoos.ttf");
    _text.setFont(*_font);
    _text.setCharacterSize(32);
    _text.setFillColor(Color::Black);
}

//update positions of GUI stuff
void PlayerLivesComponent::update(double dt) {
    //convert view coordinates to world coordinates to ensure the GUI is always drawn at the top left corner of the view!!
    auto pos = Engine::GetWindow().mapPixelToCoords(Vector2i(0, 0));
    _panel.setPosition(pos);

    //update text
    _text.setPosition(_panel.getPosition().x, _panel.getPosition().y);
    _text.setString("HP " + std::to_string(_lives));
}

void PlayerLivesComponent::render() {
    //render panel and text
    Renderer::queue(&_panel);
    Renderer::queue(&_text);
}

//increases the number of lives by adding num to current lives
void PlayerLivesComponent::increaseLives(int num) {
    _lives += num;
    //make sure lives are not more than the set maximum
    if(_lives > _maxLives) {
        _lives = _maxLives;
    }
}

//decreases lives by num
void PlayerLivesComponent::decreaseLives(int num) {
    _lives -= num;
    //make sure lives are not less than zero
    if(_lives < 0) { 
        //if they are 
        _lives = 0;
        //the player is dead
        _parent->setForDelete();
    }
}

//returns lives
int PlayerLivesComponent::getLives() const {
    return _lives;
}
