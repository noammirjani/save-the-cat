#pragma once
#include "Resources.h"
#include "Macros.h"
#include <SFML/Graphics.hpp>
#include "Board.h"
#include"GameScreen.h"
#include"Enemy.h"
#include "Level.h"

class Controller
{
public:
	//c-tor, d-tor
	Controller();
	~Controller() {}

	//FUNCTIONS
	void run();

private:
	//sfml
	sf::RenderWindow m_window;
	sf::Event        m_event;
	sf::Sprite       m_background;

	//data
	bool             m_running;
	int              m_level;
	unsigned int     m_stepCounter;

	//objects
	Board            m_board;
	GameScreen       m_screen;
	Enemy            m_enemy;
	Level            m_StageController;

	//FUNCTIONS
	void setLevel(const int = PASS_LEVEL);
	void display();
	void manageEvent();
	void handleClickEvent();
	void handleMouseMovedEvent();
	void displayGameEvent();
	bool handleClickBoard(const sf::Vector2f mouseLoc);
	void handleClickButtons(const sf::Vector2f mouseLoc);
};
