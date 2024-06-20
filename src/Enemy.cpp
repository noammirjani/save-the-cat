#include "Enemy.h"

//-------------------------------CONSTRUCTOR ----------------------------------
Enemy::Enemy(Board* board, const location location) 
	: m_boardPtr(board), m_location(location), m_preLocations(location),m_frameDirection({ 0,0 }),   
	  m_isStuck(false), m_move(false), m_stopBfs(false), m_reverseMove(false)
{
	initializeSprite(); 
}


//                                 GET FUNCTIONS                              //
//---------------------------------- isInMove ---------------------------------
bool Enemy::isInMove()const
{
	return m_move;
}


//--------------------------------- isEnemyLose -------------------------------
bool Enemy::isEnemyLose() const
{
	return m_isStuck;
}


//---------------------------------- isEnemyWin -------------------------------
bool Enemy::isEnemyWin() const
{
	return isDest(m_preLocations.top()) && !m_move;
}


//------------------------------------ isDest ---------------------------------
bool Enemy::isDest(location location) const
{
	return location.x == 0 || location.x == 10 || location.y == 0 || location.y == 10;
}



//                                 SET THE OBJECT                            //
//----------------------------  initializeSprite ------------------------------
// initialize the sprite data 
//-----------------------------------------------------------------------------
void Enemy::initializeSprite()
{
	m_sprite.setTexture(Resources::getInstance().getEnemyTexture());
	m_sprite.setPosition(m_boardPtr->getPosition(m_location));
	m_sprite.setOrigin({7,10});
	m_sprite.setScale({2,2});
	setTextureRect();
}


//------------------------------- setTextureRect ------------------------------
// set the sprite frame rect from texture
//-----------------------------------------------------------------------------
void Enemy::setTextureRect()
{
	m_sprite.setTextureRect(sf::IntRect(m_frameDirection.x * SPRITE_SIZE,
									    m_frameDirection.y * SPRITE_SIZE, 
										SPRITE_SIZE, SPRITE_SIZE));
}


//--------------------------------------- set ---------------------------------
// initialize all the enemy Characteristics
//-----------------------------------------------------------------------------
void Enemy::set()
{
	//set members
	m_preLocations.clear();
	m_frameDirection = { 0,0 };
	m_isStuck = m_move = m_stopBfs = m_reverseMove = false;

	//location
	m_boardPtr->setBlockedTiles(ENEMY_LOC, m_location);
	m_location = ENEMY_LOC;
	m_preLocations.push(ENEMY_LOC);

	//sprite
	m_sprite.setPosition(m_boardPtr->getPosition(m_location));
	setTextureRect();
}


//------------------------------------ setSprite ------------------------------
// set the sprite Characteristics
//-----------------------------------------------------------------------------
void Enemy::setSprite(const position offset)
{
	calcFrame();
	setTextureRect();
	m_sprite.setPosition(m_sprite.getPosition() + offset);
	m_sprite.setOrigin({ 7,10 });
}


//------------------------------ updateMoveData -------------------------------
// after valid move, update the enemy Characteristics for moving sprite sheet 
//-----------------------------------------------------------------------------
void Enemy::updateMoveData(const int spriteDirection, const location loc)
{
	m_location = loc;
	m_frameDirection.y = spriteDirection;
	m_frameDirection.x = -1;
	m_move = true;
}


//------------------------------------- calcFrame -----------------------------
// for the anumation after n each rendering, move to the next frame in movment 
// in the current sprite sheet for each movment there are 7 positions 
//-----------------------------------------------------------------------------
void Enemy::calcFrame()
{
	m_frameDirection.x++;
	m_frameDirection.x %= 7;
}



//									DIRECTION								 //
//----------------------------- getDirectionOffset ----------------------------
// gets an enum value for direction, for the current fitted row returns the cordinates
//-----------------------------------------------------------------------------
sf::Vector2i Enemy::getDirectionOffset(const int dirEnum) const
{
	return m_location.x % 2 == 0 ? EVEN_ROW_DIRECTIONS[dirEnum] : ODD_ROW_DIRECTIONS[dirEnum];
}


//-------------------------------- escapeEnemyDirection -----------------------
// used for the escaping animation of the enemy. for the fitted location of
// the enemy in board choose the fitted direction to run.
//  for enemy that found in loc (10, 3) its found in the bottom of the map so 
// the cat will run to the end of the window. 
//-----------------------------------------------------------------------------
std::pair<int, sf::Vector2f> Enemy::escapeEnemyDirection() const
{
	if (m_location.x == 0)  return { NW,   {0.f, -9.f } };
	if (m_location.y == 0)  return { WEST, {-9.f, 0.f}  };
	if (m_location.x == 10) return { SE,   {0.f, 9.f}   };
	if (m_location.y == 10) return { EAST, {9.f, 0.f }  };

	return { 0, {0,0} };
}


//---------------------------------- findDirection ----------------------------
// gets the current row the enemy need to move for and the mod -
//  {1 =  regular, moving forward, -1 = in undo mode, returning backwards} 
// if the kind of the row sends the fitted vector of offsets of directions
//-----------------------------------------------------------------------------
int Enemy::findDirection(const int row, const int mode) const
{
	if (row % 2 == 0)
	{
		return findEnumDir(EVEN_ROW_DIRECTIONS, mode);
	}
	return findEnumDir(ODD_ROW_DIRECTIONS, mode);
}


//----------------------------------- findEnumDir -----------------------------
// gets a vector of locations of positions and mode: 1 = regular, -1 = backwards
// searches the offset between the future loc to the current loc and multipates 
// by the mode value. 
// for the undo movment each movment is the opposite of the last one, so if the
// difference betwwen the future to curr is {1,1}, to return we need {-1,-1}
//-----------------------------------------------------------------------------
int Enemy::findEnumDir(const std::vector<location> vec, const int mode) const
{
	auto temp = (m_location - m_preLocations.top()) * mode;

	for (auto i = 0; i < vec.size(); i++)
	{
		if (vec[i] == temp) return i;
	}
	return 0;
}



//									MOVE									 //
//---------------------------------- move -------------------------------------
// move function, if the Bfs flag is turned off find the movment with bfs else 
// rand the directions. after those function if it found that the level didnt 
// end and there is valid movment the flag m_move turned on and update board in
// the next postion that wont be posible for user to stand on 
//-----------------------------------------------------------------------------
void Enemy::move()
{
	if (isDest(m_location))
	{ 
		m_preLocations.push(m_location); 
		m_move = true; 
		return; }

	if (!m_stopBfs)
	{
		findShortestPath();
	}
	else
	{
		moveByRandDirection();
	}
	
	if (m_move) m_boardPtr->setBlockedTiles(m_location, m_preLocations.top());
}


//---------------------------------- moveByRandDirection ----------------------
// rands a direction, for the current map there are in each circle 6 adjectedcs.
// sends to check if the new direction is avaiaable, if it is update data, else
// try the next direction (mod6)
// if after 6 direction(all the direction) there are not any avaiable turn on the
// stuck flag to known the controller that the user won in this level
//-----------------------------------------------------------------------------
void Enemy::moveByRandDirection()
{
	location loc;

	for (int i = 0, dir = rand()%6; i < 6; ++i, ++dir)
	{
		loc = getDirectionOffset(dir%6) + m_location;

		if (m_boardPtr->isValidPosition(loc))
		{	
			updateMoveData(dir % 6, loc);
			return;
		}
	}
	m_isStuck = true;
}


//------------------------------------- BFS -----------------------------------
// Function to perform the BFS traversal, if there found that none path is valid
// turn the BFS flag
//-----------------------------------------------------------------------------
bool Enemy::BFS(location pred[][NUM_OF_TILES], location& dest)
{
	//t - visited, f - unvisited
	bool visited[NUM_OF_TILES][NUM_OF_TILES] = { {false} };
	//Stores indices of the matrix cells
	std::queue<location> q;

	// Mark the starting cell as visited and push it into the queue
	q.push(m_location);
	visited[m_location.x][m_location.y] = true;

	// Iterate while the queue is not empty
	while (!q.empty())
	{
		sf::Vector2i cell = q.front();
		q.pop();

		// Go to the adjacent cells
		for (int i = 0; i < 6; i++)
		{
			auto adj = cell;
			if (cell.x % 2 == 0) adj += EVEN_ROW_DIRECTIONS[i];
			else                 adj += ODD_ROW_DIRECTIONS[i];

			if (m_boardPtr->isValidPosition(adj) && !visited[adj.x][adj.y]) // If cell is already visited
			{
				q.push(adj);
				visited[adj.x][adj.y] = true;
				pred[adj.x][adj.y] = cell;
				if (isDest(adj))
				{
					dest = adj;
					return true;
				}
			}
		}
	}
	m_stopBfs = true;
	return false;
}


//------------------------------- findShortestPath ----------------------------
// define matrix to hold the hole path throw bfs from the source loc to the target 
// if there is any, for that fill all the matrix in {-1,-1}, will sign in the decreptinf
// that we got to unvalid tile so there isnt a valid path!
// if the bfs returned false, there isnt a path to the end of the map, rand direction
// until the cat will be fully circled 
//-----------------------------------------------------------------------------
void Enemy::findShortestPath()
{
	location dest, pred[NUM_OF_TILES][NUM_OF_TILES];
	std::fill(*pred, *pred + NUM_OF_TILES * NUM_OF_TILES, location(-1, -1));

	if (!BFS(pred, dest)) { moveByRandDirection(); return; }

	updateMoveData(findDirection(m_preLocations.top().x), m_location = findNextStep(pred, dest));
}


//----------------------------------- findNextStep ----------------------------
// matrix path stores the shortest path, he function decrypting it from the matrix.
// in each loc in matrix that had found in the bfs there saved the pre loc that had
// found him. 
//-----------------------------------------------------------------------------
location Enemy::findNextStep(const location pred[][NUM_OF_TILES], const location dest)
{
	std::vector<location> path;
	sf::Vector2i crawl = dest;

	path.push_back(crawl);
	while (pred[crawl.x][crawl.y] != m_location || pred[crawl.x][crawl.y] == location{ -1,-1 })
	{
		path.push_back(pred[crawl.x][crawl.y]);
		crawl = pred[crawl.x][crawl.y];
	}

	return crawl;
}


//-------------------------------------- undo ---------------------------------
// if it called while in the stack only the first beg location -> return false
// else pop the last pos (current loc) find the frame and turn the flags on 
//-----------------------------------------------------------------------------
bool Enemy::undo()
{
	if (m_preLocations.size() == 1) return false;

	m_preLocations.freeObj();
	m_frameDirection.y = findDirection(m_location.x, m_frameDirection.x = -1);
	m_reverseMove = m_move = true;

	return true;
}


//----------------------------------- enemyEscape -----------------------------
// the enemy escape anumation. send to func that returns the direction of the escape 
// and the offset of the movment in each rendering
// if the sprite postion is on the window edges -> so the user cannot see him anymore 
// stop the animation update the flag to off
//-----------------------------------------------------------------------------
void Enemy::enemyEscape(sf::RenderWindow& window)
{
	window.setFramerateLimit(15);

	auto p = m_sprite.getPosition();
	auto t = escapeEnemyDirection();

	m_frameDirection.y = t.first;
	setSprite(t.second);				//send the shift
	window.draw(m_sprite);

	//left                    up                  right                     down
	if (p.x < -50.f || p.y < -50.f || p.x > WINDOW_WIDTH + 25 || p.y > WINDOW_HEIGHT + 25)
	{
		window.setFramerateLimit(60);
		m_move = false;
	}
}

	
//									PRINT									 //	
//----------------------------------- print -----------------------------------
// define between escaping, movment(regular/reverse) and standing
//-----------------------------------------------------------------------------
void Enemy::print(sf::RenderWindow& window)
{
	if (isDest(m_preLocations.top()) && m_move)
	{
		enemyEscape(window);
	}

	else if (m_move)
	{
		printMove(m_boardPtr->getPosition(m_preLocations.top()),
			m_boardPtr->getPosition(m_location), window);
	}

	else
	{
		window.draw(m_sprite);
	}
}


//---------------------------------- printMove --------------------------------
// for the movment there is 7 position, so divide the deffernce between source 
// and target position, if it got to the frame 6 -> so all the movment has been
// printed 
//-----------------------------------------------------------------------------
void Enemy::printMove(position posCurr, position posNext, sf::RenderWindow& window)
{
	window.setFramerateLimit(25);
	if (m_reverseMove) setSprite((posCurr - posNext) / 7.f);
	else               setSprite((posNext - posCurr) / 7.f); //send the shift
	window.draw(m_sprite);

	if (m_frameDirection.x == 6)  //set the momvment to off
	{
		if (m_reverseMove)	reverseStopPrint(posCurr);
		else 				moveStopPrint(posNext);

		if (m_location == ENEMY_LOC) //set to start position
		{
			m_frameDirection = { 0,0 };
			setSprite({ 0,0 });
		}

		m_move = false;
		window.setFramerateLimit(60);
	}
}


//------------------------------- reverseStopPrint ----------------------------
// update all the data that needed to stop the print movment 
//-----------------------------------------------------------------------------
void Enemy::reverseStopPrint(const position loc)
{
	m_reverseMove = false;
	m_boardPtr->setBlockedTiles(m_preLocations.top(), m_location);
	m_location = m_preLocations.top();
	m_sprite.setPosition(loc);
}


//--------------------------------- moveStopPrint -----------------------------
// update all the data that needed to stop the print movment 
//-----------------------------------------------------------------------------
void Enemy::moveStopPrint(const position loc)
{
	if (!isDest(m_location))
	{
		m_preLocations.push(m_location);
	}
	m_sprite.setPosition(loc);
}