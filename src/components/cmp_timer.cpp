#include "cmp_timer.h"
#include <engine.h>
#include <settings_parser.h>

using namespace sf;

/*
* This component will keep track of how much time the player takes to complete a level and display a timer.
*/

SettingsParser sp;

//create panel and start the timer
TimerComponent::TimerComponent(Entity *p) : Component(p), 
                                            _panel(Panel(Vector2f(100.f, 0), Vector2f(200.f, 32.f), "Anonymous.ttf")), _timer(0) {
    sp.readFile("res/lang/en.txt");
    _panel.setPanelColour(Color(192, 192, 192, 128));
}

//update panel and set its text
void TimerComponent::update(double dt) {
    //cast the time to an int because we don't want it to be displayed as a float (e.g. 1.00000)
        if(!Engine::isPaused()) {
                _timer += dt;
        }
    _panel.setTextLocalised(sp.get("time") + " " + std::to_string((int)(_timer)));
    _panel.update(dt);
}
//render the panel
void TimerComponent::render() {
    _panel.render();
}

int TimerComponent::getTime() const {
    return (int)_timer;
}