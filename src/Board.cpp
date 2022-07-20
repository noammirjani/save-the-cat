#include"Board.h"


//-------------------------------- CONSTRUCTOR --------------------------------
Board::Board() : m_boardSize(NUM_OF_TILES), m_map()
{
	intalizeMap();
}

//										SET									//
//------------------------------ intalizeMap ----------------------------------
// det the map to an matrix of sf::circle, for each circle set the place and place
//----------------------------------------------------------------------------
void Board::intalizeMap()
{
	auto tempCircle = getCircle();
	std::vector<sf::CircleShape> tempVec;

	for (int row = 0; row < m_boardSize; ++row)
	{
		tempVec.clear();
		for (int col = 0; col < m_boardSize; ++col)
		{
			tempCircle.setPosition(getPosition(row, col)); 
			tempVec.emplace_back(tempCircle);
		}
		m_map.emplace_back(tempVec);
	}
}


//---------------------------------- resetMap ---------------------------------
// free all the stack locations, set the matrix circles to clear the outline 
//----------------------------------------------------------------------------
void Board::resetMap()
{
	while (!m_occupiedTiles.isEmpty())
	{
		undo();
	}

	for (auto& vec : m_map)
	{
		for (auto& circle : vec)
		{
			circle.setOutlineColor(CLEAR);
		}
	}
}


//-----------------------------------  setBoard -------------------------------
// get the vec that holds the randomies locations for the occupied tiles
// set all the matrix to the AVAILA, then runs on the vector and for each loc
// enterOCCUPIED color
//-----------------------------------------------------------------------------
void Board::setBoard(const std::vector<location> occupiedTiles)
{
	resetMap();							  //clear the map data

	for (auto& vec : m_map)				  //set all the map to clear 
	{
		for (auto& circle : vec)
		{
			circle.setFillColor(AVAILABLE);
		}
	}

	for (const auto& tile : occupiedTiles) //update the randomies tile 
	{
		m_map[tile.x][tile.y].setFillColor(OCCUPIED);
	}
}


//----------------------------------- intilaizeColor --------------------------
// for each colored outile set back to clear 
//-----------------------------------------------------------------------------
void Board::intilaizeColor(sf::CircleShape& circle)
{
	if (circle.getOutlineColor() == BLOCK_MOVE || circle.getOutlineColor() == UNBLOCK_MOVE)
	{
		circle.setOutlineColor(CLEAR);
	}
}
 

//------------------------------------- colorCircle ---------------------------
//if the circle color AVAILABLE, change the outline to blue else anything else 
// is blocked tile (becouse user chose it alreadyy or the cat sdtands there)
//-----------------------------------------------------------------------------
void Board::colorCircle(sf::CircleShape& circle)
{
	if (circle.getFillColor() == AVAILABLE)
	{
		circle.setOutlineColor(UNBLOCK_MOVE);
	}
	else
	{
		circle.setOutlineColor(BLOCK_MOVE);
	}
}


//----------------------------------- setBlockedTiles -------------------------
// gets to location, the next and the perv of the cat, the next need to be update 
// to block and the perc to unblock ot 
//-----------------------------------------------------------------------------
void Board::setBlockedTiles(const location locationToBlock, const location locationToRelese)
{
	m_map[locationToRelese.x][locationToRelese.y].setFillColor(AVAILABLE);
	m_map[locationToBlock.x][locationToBlock.y].setFillColor(ENEMY);
}


//										GET									  //
//----------------------------------- getCircle -------------------------------
sf::CircleShape Board::getCircle() const
{
	sf::CircleShape tempCircle(RADIUS);
	tempCircle.setFillColor(AVAILABLE);
	tempCircle.setOutlineThickness(2.f);
	tempCircle.setOutlineColor(CLEAR);
	return tempCircle;
}


//----------------------------------- getPosition -----------------------------
sf::Vector2f Board::getPosition(const int row, const int col) const
{
	float sideRange;
	row % 2 == 0 ? sideRange = EVEN : sideRange = ODD;
	return sf::Vector2f(sideRange + (SIZE + SIDE) * col, (row * (SIZE + UP)) + RANGE_UP);
}


//----------------------------------- getPosition -----------------------------
sf::Vector2f Board::getPosition(const location location) const
{
	return getPosition(location.x, location.y);
}


//-------------------------------------- getBoard -----------------------------
const std::vector<std::vector<sf::CircleShape>> Board::getBoard() const
{
	return m_map;
}


//------------------------------------- isValidPosition -----------------------
bool Board::isValidPosition(location location) const
{
	return isInBounds(location) && m_map[location.x][location.y].getFillColor() == AVAILABLE;
}


//------------------------------------- isInBounds ----------------------------
bool Board::isInBounds(location location) const
{
	return location.x >= 0 && location.x < 11 && location.y >= 0 && location.y < 11;
}


//------------------------------------ getIndex -------------------------------
// gets position and encrypted it to location
//-----------------------------------------------------------------------------
sf::Vector2i Board::getIndex(const position position) const
{
	int sideRange;
	int row = (position.y - RANGE_UP) / (SIZE + UP);
	row % 2 == 0 ? sideRange = EVEN : sideRange = ODD;
	int col = (position.x - sideRange) / float(SIZE + SIDE);
	return { row,col };
}


//								FUNCTUNALITY								 //	
//---------------------------------- print ------------------------------------
void Board::print(sf::RenderWindow& window)
{	
	for (auto& vec : m_map)
	{
		for (auto& circle : vec)
		{
			window.draw(circle);
		}
	}
}


//------------------------------- validClick ----------------------------------
// gets position of the mouse, checks if it located in one of the map avaiable circles, 
// if it is enter the new locaton to the stack, check the color and change the outline color
//-----------------------------------------------------------------------------
bool Board::validClick(const position location)
{
	for (auto& vec : m_map)
	{
		for (auto& circle : vec)
		{
			if (circle.getGlobalBounds().contains(location) && circle.getFillColor() == AVAILABLE)
			{
				m_occupiedTiles.push(getIndex(circle.getPosition()));
				circle.setFillColor(OCCUPIED);
				circle.setOutlineColor(BLOCK_MOVE);
				return true;
			}
		}
	}
	return false;
}


//------------------------------- truckMouse ----------------------------------
// gets position of the mouse, checks if it located in one of the map circles, 
// if it is change it to the fitted outline color, fits to the filled color
//-----------------------------------------------------------------------------
void Board::truckMouse(const position location)
{
	for (auto& vec : m_map)
	{
		for (auto& circle : vec)
		{
			if (circle.getGlobalBounds().contains(location))
			{
				colorCircle(circle); 
			}
			else
			{
				intilaizeColor(circle);
			}
		}
	}
}


//--------------------------------- undo --------------------------------------
// for the undo option, pop the last location from the stack and color it to 
// avaliable 
//-----------------------------------------------------------------------------
bool Board::undo()
{
	if (m_occupiedTiles.isEmpty()) return false;

	auto tileToDelete = m_occupiedTiles.pop();
	m_map[tileToDelete.x][tileToDelete.y].setFillColor(AVAILABLE);
	return true;
}
