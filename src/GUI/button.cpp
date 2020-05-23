#include "button.h"
#include "../../engine/src/engine.h"
#include "../../engine/src/system_renderer.h"
#include <settings_parser.h>

using namespace sf;

//constructor, sets size and text
Button::Button(const Vector2f& pos, const Vector2f& size, const std::string& text)
	: _check(true)
	, _timer(0.2f)
	, _panel(Panel(pos, size))

{
	_panel.setTextLocalised(text);
	_panel.setTextSize(30);
	_panel.setGUI(false);
	_panel.setBorder(4.f, Color::White);
	_panel.setTextColour(Color::White);
	_position = pos;
	_clicked = false;
}

//sets position of the button
void Button::setPosition(const Vector2f& pos)
{
	_panel.setPositionOfCentre(pos);
	_position = pos;
	_label.setPositionOfCentre(pos - Vector2f(300.f, 0));
}

//checks for clicks or if the mouse is over the button
void Button::update(double dt)
{
	//_label.setPositionOfCentre(Vector2f(_panel.getPositionOfCentre().x - 200.f, _panel.getPositionOfCentre().y));
	_label.update(dt);

	_clicked = false;

	auto mouseBox = getMouseRect(12, 12);
	auto btnRect = _panel.getBoundingBox();

	if(mouseBox.intersects(btnRect))
	{
		onHover();
	}
	else
	{
		reset();
	}

	if(mouseBox.intersects(btnRect) && Mouse::isButtonPressed(Mouse::Left) && _check)
	{
		onClick();
		_clicked = true;
		_check = false;
	}
	if(!_check)
	{
		_timer -= dt;
	}
	if(_timer <= 0.0f)
	{
		_timer = 0.2f;
		_check = true;
	}
}

//renders the button and the text
void Button::render()
{
	_panel.render();
	_label.render();
}

//called when the button is clicked
void Button::onClick() { _panel.setPanelColour(Color::White); }

//called when the mouse is on top the button
void Button::onHover()
{
	_panel.setBorder(4.f, Color(54, 18, 179));
	_panel.setPanelColour(Color(0, 204, 255));
}

//called when the mouse is NOT on top of the button
void Button::reset()
{
	_panel.setPanelColour(Color(0, 46, 138));
	_panel.setBorder(2.f, Color::White);
	//_panel.setBorder(0, Color::Transparent);
}

//returns the "hitbox" of the mouse
FloatRect Button::getMouseRect(unsigned int width, unsigned int height)
{
	FloatRect mouseBox;
	mouseBox.width = width;
	mouseBox.height = height;
	mouseBox.left = Mouse::getPosition(Engine::GetWindow()).x;
	mouseBox.top = Mouse::getPosition(Engine::GetWindow()).y;

	return mouseBox;
}

//returns whether the button has been clicked
bool Button::isClicked() const { return _clicked; }

const sf::Vector2f& Button::getPosition() { return _position; }

void Button::addLabel(const std::string& text)
{
	const auto pos = _panel.getPosition();
	const auto labelPos = Vector2f(pos.x - 200.f, pos.y - 5.f);
	_label = Panel(labelPos, Vector2f(100.f, 50.f));
	_label.setPositionOfCentre(labelPos);
	_label.setTextLocalised(text);
	_label.setPanelColour(Color::Transparent);
	_label.setTextColour(Color::White);
	_label.setGUI(false);
}

const std::string& Button::getSelection() const
{
	static const std::string ret = std::string();
	return ret;
}

void Button::setSelection(const std::string& sel)
{
	//do nothing
}
