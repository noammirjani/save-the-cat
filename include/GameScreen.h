#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Board.h"
#include "Button.h"
#include "Resources.h"

class GameScreen
{
public:
	//c-tor, d-tor
	GameScreen();
	~GameScreen() {}

	//public functions 
	void print(sf::RenderWindow&, const int, const unsigned int);
	void truckMouse(const sf::Vector2f);
	void runLoadScreen(sf::RenderWindow&, const int);
	int  validClick(const sf::Vector2f);
private:
	//members to print the data 
	sf::Text m_text;
	std::vector<Button> m_buttons;

	//aux functions
	void intializeText();
	void printText(sf::RenderWindow&, const int, const sf::Vector2f); 
};