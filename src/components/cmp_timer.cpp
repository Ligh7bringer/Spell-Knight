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
                                            _panel(Panel(Vector2f(100.f, 0), Vector2f(200.f, 32.f), "Anonymous.ttf")) {
    sp.readFile("res/lang/en.txt");
    _panel.setPanelColour(Color(192, 192, 192, 128));
    _paused = false;
    _runTime =0;
    _clock.restart();
}

//update panel and set its text
void TimerComponent::update(double dt) {
    //cast the time to an int because we don't want it to be displayed as a float (e.g. 1.00000)
    if(_paused){
        _clock.restart();
    }
    _paused = false;
    //_panel.setTextLocalised(sp.get("time") + " " + std::to_string((int)(_clock.getElapsedTime().asSeconds())));
    _panel.setTextLocalised(sp.get("time") + " " + std::to_string(getTime()));
    _panel.update(dt);
}

void TimerComponent::Pause(){
    if(!_paused){
        _runTime += _clock.getElapsedTime().asSeconds();
    }
    _paused = true;
}
//render the panel
void TimerComponent::render() {
    _panel.render();
}

int TimerComponent::getTime() const {
    if(!_paused){
        return (int) (_runTime +_clock.getElapsedTime().asSeconds());
    }
    return (int) _runTime;

}