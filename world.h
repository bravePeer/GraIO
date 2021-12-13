#pragma once
#include <SFML/Graphics.hpp>
#include "utilities.h"

#define TILEH	128
#define TILEW	256

using namespace sf;

enum
{//   0       1       2
	Zwykle, Drewno, Kamien
};

struct Tile
{
	Sprite* ground = nullptr;
	Sprite* building = nullptr;
	Sprite* unit = nullptr;
	Vector2i size = { 1,1 };
};

class World
{
public:
	World()
	{}
	World(Vector2i _worldSize)
	{
		groundTexture[0].loadFromFile("Resources\\Textures\\Ground\\testgreen.png");
		groundTexture[1].loadFromFile("Resources\\Textures\\Ground\\tilefe.png");
		groundTexture[2].loadFromFile("Resources\\Textures\\Ground\\tiletree.png");
		groundSprites = new Sprite[3];

		groundSprites[0].setTexture(groundTexture[0]);
		groundSprites[1].setTexture(groundTexture[1]);
		groundSprites[2].setTexture(groundTexture[2]);

		worldSize = _worldSize;
		tiles = new Tile[worldSize.x * worldSize.y];
		for (int i = 0; i < worldSize.x; i++)
		{
			for (int j = 0; j < worldSize.y; j++)
			{
				tiles[i + j * worldSize.x].ground = &groundSprites[0];
			}
		}

		tiles[0].ground = &groundSprites[1];
	}
	~World()
	{
		delete groundSprites;
		delete tiles;
	}

	void Render(RenderTarget* target)
	{
		for (int i = 0; i <worldSize.x; i++)
		{
			for (int j = 0; j < worldSize.y; j++)
			{
				tiles[i + j * worldSize.x].ground->setPosition(ScreenPos({ i,j }, { TILEW,TILEH }));

				target->draw(*tiles[i + j * worldSize.x].ground);
			}
		}
	}
private:
	Texture groundTexture[3];
	Sprite* groundSprites = nullptr;

	Vector2i worldSize = {0,0};
	Tile* tiles = nullptr;
};
