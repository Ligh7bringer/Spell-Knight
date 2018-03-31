#include "cmp_timer.h"

using namespace sf;

/*
* This component will keep track of how much time the player takes to complete a level and display a timer.
*/

//create panel and start the timer
TimerComponent::TimerComponent(Entity *p) : Component(p), 
                                            _panel(Panel(Vector2f(100.f, 0), Vector2f(200.f, 32.f), "DoctorSoos.ttf")) {
    _panel.setPanelColour(Color(192, 192, 192, 128));
    _clock.restart();
}

//update panel and set its text
void TimerComponent::update(double dt) {
    //cast the time to an int because we don't want it to be displayed as a float (e.g. 1.00000)
    _panel.setText("Time " + std::to_string((int)(_clock.getElapsedTime().asSeconds())));
    _panel.update(dt);
}

//render the panel
void TimerComponent::render() {
    _panel.render();
}