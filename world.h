#pragma once
#include <SFML/Graphics.hpp>
#include "tile.h"
#include <vector>

#ifndef WORLD_H
#define WORLD_H

class World
{
private:

	void SetUpInitialState();
	void SetUpEnemyPositions();
	void SetUpTiles();

public:
	std::vector<std::vector<Tile*>>tiles;
	int gridLenght;
	World();
};

#endif
