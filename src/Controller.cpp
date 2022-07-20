#include "Controller.h"

//------------------------------ CONSTRUCTOR ----------------------------------
Controller::Controller() : m_window({ WINDOW_WIDTH, WINDOW_HEIGHT }, "CIRCLE THE CAT!"), m_running(true),
						   m_level(1), m_stepCounter(0), m_event(), m_enemy(&m_board, ENEMY_LOC),
						   m_StageController()
{	
	m_background = Resources::getInstance().getBackgroud(BACKGROUND);
	m_background.setPosition(0,0);
}


//-------------------------------------- run ----------------------------------
// control the game 
//-----------------------------------------------------------------------------
void Controller::run()
{
	setLevel();
	
	while (m_window.isOpen())
	{
		if (m_level <= DIFFCULTIES)
		{
			manageEvent();
			display();	
		}

		else m_window.close();
	}
}


//------------------------------------ setLevel -------------------------------
// set all the objects and parameter in the game to a new level or to reset the 
// current level
//-----------------------------------------------------------------------------
void Controller::setLevel(const int gameMode)
{
	m_stepCounter = 0;
	m_enemy.set();

	if (gameMode) m_board.setBoard(m_StageController.createLevel(m_level));
	else          m_board.resetMap();
	
}


//------------------------------------- display -------------------------------
// mange the prints of the game 
//-----------------------------------------------------------------------------
void Controller::display()
{
	m_window.clear();
	m_window.draw(m_background);
	m_board.print(m_window);
	m_screen.print(m_window, m_level, m_stepCounter);
	m_enemy.print(m_window);
	displayGameEvent();
	m_window.display();
}


//----------------------------------- manageEvent -----------------------------
// main loop to manage the events 
//-----------------------------------------------------------------------------
void Controller::manageEvent()
{
	while (m_window.pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case CLOSE_WINDOW:
			m_window.close();
			break;

		case BUTTON_CLICKED:
			handleClickEvent();
			break;

		case MOUSE_MOVED:
			handleMouseMovedEvent();
			break;
		}
	}
}


//---------------------------------- handleClickEvent -------------------------
// handle Click Event 
//-----------------------------------------------------------------------------
void Controller::handleClickEvent()
{
	if (m_enemy.isInMove()) return; //stop user interrupt while the enemy runs from the window  

	auto mouseLoc = m_window.mapPixelToCoords({ m_event.mouseButton.x, m_event.mouseButton.y });

	if (!handleClickBoard(mouseLoc))
	{
		handleClickButtons(mouseLoc);
	}
}


//----------------------------------- handleClickBoard ------------------------
// handle Click Event in board, sends to board if found that the click is on 
// valid map object, move the enemy and update the step counter 
//-----------------------------------------------------------------------------
bool Controller::handleClickBoard(const sf::Vector2f mouseLoc)
{
	if (m_board.validClick(mouseLoc))
	{
		m_stepCounter++;
		m_enemy.move();
		return true;
	}
	return false;
}


//---------------------------------- handleClickButtons -----------------------
// handle Click Event in board, sends to screen, if the click is on the buttons 
// to the fitted act
//-----------------------------------------------------------------------------
void Controller::handleClickButtons(const sf::Vector2f mouseLoc)
{
	switch (m_screen.validClick(mouseLoc))
	{
	case RESET:
		setLevel(RESET);
		break;

	case UNDO:
		if (m_board.undo() && m_enemy.undo())
			--m_stepCounter;
		break;
	};
}


//----------------------------------- handleMouseMovedEvent -------------------
//handleMouseMovedEvent, check in board and check in screen functions (buttons)
//-----------------------------------------------------------------------------
void Controller::handleMouseMovedEvent()
{
	if (m_enemy.isInMove()) return;

	auto mouseLoc = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
	m_board.truckMouse(mouseLoc);
	m_screen.truckMouse(mouseLoc);
}


//------------------------------------ displayGameEvent -----------------------
// check if the level endded (enemy lose = user win or the opposite)
// update the fitted data and print the fitted load screen 
//-----------------------------------------------------------------------------
void Controller::displayGameEvent()
{ 
	if (m_enemy.isEnemyWin())
	{
		m_screen.runLoadScreen(m_window, LOSE);
		setLevel(LOSE);
	}

	else if (m_enemy.isEnemyLose())
	{
		++m_level;

		if (m_level > DIFFCULTIES) { m_screen.runLoadScreen(m_window, WIN); return; }

		m_screen.runLoadScreen(m_window, PASS_LEVEL);
		setLevel(PASS_LEVEL);
	}
}