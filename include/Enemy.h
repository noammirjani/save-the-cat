#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <algorithm>
#include "Resources.h"
#include "Board.h"


//the main objecct of the game - the enemy(computer)
// that plays against the user
class Enemy
{
public:
	//c-tor, d-tor
	Enemy(Board*, const location);
	~Enemy() {}

	//functions
	void set();
	bool undo();
	void move();
	//print
	void print(sf::RenderWindow&);
	//get functions
	bool isEnemyLose()      const; 
	bool isEnemyWin() const; 
	bool isInMove()const;

private:
	//bool members 
	bool m_reverseMove; 
	bool m_isStuck; 
	bool m_move;
	bool m_stopBfs;
	//sprite 
	sf::Sprite m_sprite; 
	sf::Vector2i m_frameDirection;
	//object data
	Board* m_boardPtr; 
	sf::Vector2i m_location; //+ stack
	Stack<sf::Vector2i> m_preLocations;

	//functions
	//sprite
	void initializeSprite(); 
	void setTextureRect();
	void setSprite(const position);
	void calcFrame();
	void enemyEscape(sf::RenderWindow&);

	//move
	void moveByRandDirection();
	bool isDest(location) const;
	void findShortestPath();
	bool BFS(location[][NUM_OF_TILES], location&);
	void updateMoveData(const int, const location);
	sf::Vector2i findNextStep(const location[][NUM_OF_TILES], const location);

	//print
	void printMove(position, position, sf::RenderWindow&);
	void reverseStopPrint(const position);
	void moveStopPrint(const position);

	//get direction
	std::pair<int, sf::Vector2f> escapeEnemyDirection() const;
	sf::Vector2i getDirectionOffset(const int) const;
	int findDirection(const int, const int = 1) const;
	int findEnumDir(std::vector<location>, const int) const;
};