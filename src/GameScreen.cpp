#include"GameScreen.h"


//----------------------------- CONSTRUCTOR -----------------------------------
GameScreen::GameScreen()
{
	intializeText();

	m_buttons.emplace_back(UNDO_POS, UNDO);
	m_buttons.emplace_back(RESET_POS, RESET);
}

  
//									SET DATA								  //
//------------------------------- intializeText -------------------------------
void GameScreen::intializeText()
{
	m_text.setFont(Resources::getInstance().getFont());
	m_text.setColor(sf::Color::Black);
	m_text.setCharacterSize(TEXT_SIZE);
}


//-------------------------------- printText -----------------------------------
void GameScreen::printText(sf::RenderWindow& window, const int data, const sf::Vector2f location)
{
	m_text.setPosition(location);
	m_text.setString(std::to_string(data));
	window.draw(m_text);
}


//---------------------------------- print -------------------------------------
void GameScreen::print(sf::RenderWindow& window, const int level, const unsigned int stepCounter)
{
	printText(window, level, LEVEL_POS);
	printText(window, stepCounter, COUNTER_POS);

	for (auto button : m_buttons)
	{
		button.draw(window);
	}
}


//--------------------------------- truckMouse --------------------------------
// 	runs on the vec of buttons checks if the locatio is contains in button, if it
// does color
//-----------------------------------------------------------------------------
void GameScreen::truckMouse(const sf::Vector2f location)
{
	for (auto& button : m_buttons)
	{
		if (button.isContain(location))
		{
			button.setColor(BUTTONS);
		}
		else
		{
			button.setColor(CLEAR);
		}
	}
}


//-------------------------------- runLoadScreen ------------------------------
// 	display load screen + music
//-----------------------------------------------------------------------------
void GameScreen::runLoadScreen(sf::RenderWindow& window, const int mode)
{
	window.draw(Resources::getInstance().getBackgroud(mode));
	Resources::getInstance().playSound(mode);
	window.display();
	sf::sleep(sf::seconds(2));
}


//-----------------------------------------------------------------------------
// 	runs on the vec of buttons checks if there were click on the button area, 
// if there was return the button type 
//-----------------------------------------------------------------------------
int GameScreen::validClick(const sf::Vector2f location)
{
	for (auto& button : m_buttons)
	{
		if (button.isContain(location))
		{
			return button.getType();
		}
	}
	return NONE;
}