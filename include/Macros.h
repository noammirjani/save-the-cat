#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using location = sf::Vector2i;
using position = sf::Vector2f;


//---------------  MOVEMENT  ------------------
//deltaTime const
//movement 
enum DIRECTIONS
{
	WEST, SW, EAST, SE, NW, NE
};

const std::vector<location> EVEN_ROW_DIRECTIONS{ {0,-1}, {1,-1}, {0,1}, {1,0}, {-1,-1}, {-1,0} };
const std::vector<location> ODD_ROW_DIRECTIONS{ {0,-1}, {1,0}, {0,1}, {1,1}, {-1,0}, {-1,1} };

//----------------  EVENTS  ------------------
const auto CLOSE_WINDOW   = sf::Event::Closed;
const auto BUTTON_CLICKED = sf::Event::MouseButtonReleased;
const auto MOUSE_MOVED    = sf::Event::MouseMoved;


//----------------  BUTTOMS DATA  -------------
//color
const auto OCCUPIED     = sf::Color(118, 128, 39);
const auto AVAILABLE    = sf::Color(218, 247, 80);
const auto ENEMY        = sf::Color(218, 246, 80);
const auto BLOCK_MOVE   = sf::Color(228, 55, 12);
const auto UNBLOCK_MOVE = sf::Color(92, 107, 239);
const auto BUTTONS      = sf::Color(218, 247, 80, 70);
const auto CLEAR        = sf::Color(0, 0, 0, 0);

//buttons location 
const auto LEVEL_POS = sf::Vector2f(815, 43);
const auto COUNTER_POS = sf::Vector2f(815, 141);
const auto UNDO_POS = sf::Vector2f(685, 536);
const auto RESET_POS = sf::Vector2f(792, 536);

//buttons size
const auto RADIUS = 25;
const auto ODD = 76;
const auto EVEN = 50;
const auto SIDE = 7.1;
const auto UP = 1;
const auto RANGE_UP = 36;
const auto SIZE = 48;

enum BUTTONS
{
	RESET, UNDO, NONE 
};



//----------------  BOARD  -------------------
const auto NUM_OF_TILES = 11;
const auto TEXT_SIZE = 32;


//---------------- WINDOW  -------------------
const int WINDOW_WIDTH = 894;
const int WINDOW_HEIGHT = 615;

//--------------- ICONE VALUES ---------------
const int  SPRITE_SIZE = 40;
const sf::Vector2i ENEMY_LOC = { 5,5 };
const sf::Vector2i DEFAULT = { 5,5 };


//--------------- CONTROLLER ----------------
const unsigned int DIFFCULTIES = 2;


//--------------- RESOURCES ----------------
enum RESOURCES
{
	LOSE, PASS_LEVEL, WIN, BACKGROUND
};

const std::vector <std::string> BACKGROUNDS = {"lose.png", "passLevel.png", "win.png","board.png" };
const std::vector <std::string> SOUNDS = { "lose.wav","win.wav","win.wav"};