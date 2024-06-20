#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Resources.h"

class Button
{
public:
	Button(const position, const int);
	~Button() {}

	//get functions 
	void draw(sf::RenderWindow&);
	bool isContain(const position);
	void setColor(const sf::Color);
	const int getType() const;

private:
	//button data
	sf::RectangleShape m_shape;
	const int          m_num;   //to define the button

};
