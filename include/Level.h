#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <ranges>
#include "Macros.h"

//the class is responsible to create a valid new level. the levels are automaticly build.
class Level
{
public:
	//c-tor, d-tor
	Level()  {}
	~Level() {}

	std::vector<location> createLevel(const int) const;

private:
	//aux
	int getDifficulty(const int) const;
	bool randTile(const std::vector<location> vec, location& tile) const;
};