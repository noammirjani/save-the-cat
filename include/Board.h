#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include "Macros.h"
#include"Stack.h"

class Board
{
public:
	//c-tor, d-tor
	Board();
	~Board() {}

	//FUNCTIONS
	bool validClick(const position);	
	void truckMouse		 (const position);
	void print			 (sf::RenderWindow&);
	void setBoard        (const std::vector<location>);
	void resetMap();
	bool undo();
	void setBlockedTiles(const location, const location);

	//get
	const std::vector<std::vector<sf::CircleShape>> getBoard() const;
	sf::Vector2f getPosition(const int, const int)			   const;
	sf::Vector2f getPosition(const location)                   const;
	bool isValidPosition(location)                             const; 
	sf::Vector2i getIndex(const position)                      const;

private:
	int m_boardSize;
	Stack<sf::Vector2i> m_occupiedTiles; 
	std::vector<std::vector<sf::CircleShape>> m_map;

	//FUNCTIONS
	void intalizeMap();
	void colorCircle(sf::CircleShape&); 
	void intilaizeColor(sf::CircleShape&); 
	 sf::CircleShape  getCircle() const; 
	 bool isInBounds(location) const;
};

