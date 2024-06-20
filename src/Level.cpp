#include "Level.h"

//------------------------------- createLevel ---------------------------------
// for the fitted level num define the rand the num of the occupied tiles.
// run in loop and rand new tile until the vector is fully on the size that had 
// been rand. return the vec.
//-----------------------------------------------------------------------------
std::vector<sf::Vector2i> Level::createLevel(const int level) const
{
	auto difficulty = getDifficulty(level);
	std::vector<location> randTiles;
	location tempTile;

	while (randTiles.size() < difficulty)
	{
		if (randTile(randTiles, tempTile))
		{
			randTiles.emplace_back(tempTile);
		}
	}
	return randTiles;
}


//---------------------------------- getDifficulty ----------------------------
//there is three diffculties in he game, for diffculties more add case  and update the 
//difficulty value in macros
//-----------------------------------------------------------------------------
int Level::getDifficulty(const int level) const
{
	switch (level)
	{
		//14 - 11
	case 1: return 14 - (rand() % 4);
		break;
		//10 - 7
	case 2: return 10 - (rand() % 4);
		break;
		//6 - 4
	case 3: return 6 - (rand() % 3);
		break;
	}

	return 0;
}

 
//------------------------------------- randTile ------------------------------
// rand location that the values runs between 0, 11, if the rand tile is not the 
// enemy location or not one of the locaition that already had been raned return 
// true(valid location), update the valod location in the refernced parameter
//-----------------------------------------------------------------------------
bool Level::randTile(const std::vector<location> vec, location& tile) const
{
	tile = { rand() % 11, rand() % 11 };
	if (std::ranges::find(vec.begin(), vec.end(), tile) == vec.end() && tile != ENEMY_LOC)
	{
		return true;
	}

	return false;
}