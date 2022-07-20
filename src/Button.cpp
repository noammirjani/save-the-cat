#include "Button.h"


//----------------------------- CONSTRUCTOR -----------------------------------
Button::Button(const position location, const int buttonNum)
	: m_num(buttonNum)
{
	m_shape.setSize(sf::Vector2f(90, 50));
	m_shape.setFillColor(CLEAR);
	m_shape.setPosition(location);
}


//--------------------------------- draw --------------------------------------
void Button::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}


//---------------------------------- isContain --------------------------------
// returns if the location is contains in the button
//-----------------------------------------------------------------------------
bool Button::isContain(const position location)
{
	return m_shape.getGlobalBounds().contains(location);
}


//--------------------------------- setColor  ---------------------------------
void Button::setColor(const sf::Color color)
{
	m_shape.setFillColor(color);
}


//---------------------------------- getType ----------------------------------
//  returns the type (num) of the button 
//-----------------------------------------------------------------------------
const int Button::getType() const
{
	return m_num;
}