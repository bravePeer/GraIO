#pragma once
#include <SFML/Graphics.hpp>
#include "utilities.h"
#include "unit.h"
#include "building.h"

#define TILEH	128
#define TILEW	256

using namespace sf;

enum GROUNDTYPES
{//   0       1       2
	NOTHING, GRASS, WOOD, STONE, IRON
};


struct Tile
{
	Sprite* ground = nullptr;	// Groun* ground
	//Sprite* building = nullptr; // 
	Building* building = nullptr;
	
								//Unit* unit = nullptr;
	Sprite* unit = nullptr;		
	unsigned int groundType = NOTHING;
	unsigned int buildingType = NOTHING;
	unsigned int unitType = NOTHING;
	Vector2i size = { 1,1 };
};

class World
{
public:
	World()
	{}
	World(Vector2i _worldSize)
	{
		groundTexture[0].loadFromFile("Resources\\Textures\\Ground\\ground.png");
		groundTexture[1].loadFromFile("Resources\\Textures\\Ground\\iron.png");
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
				tiles[i + j * worldSize.x].groundType = GRASS;
			}
		}

		tiles[0].ground = &groundSprites[1];
		tiles[4].ground = &groundSprites[1];
		tiles[7].ground = &groundSprites[1];
	
		tiles[4].groundType = IRON;
		tiles[0].groundType = IRON;
		tiles[7].groundType = IRON;
	}
	~World()
	{
	//	if(groundSprites)
		//	delete groundSprites;
		for (int i = 0; i < worldSize.x*worldSize.y; i++)
		{
			delete tiles[i].building;
		}
		delete tiles;
	}

	//void AddUnit(Unit* _unit)
	//{
	//
	//}
	//void RemoveUnit(Unit* _unit)
	//{
	//
	//}
	Tile* GetTile(Vector2i posWolrd)
	{
		return &tiles[posWolrd.x + posWolrd.y * worldSize.x];
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
	void SetBuilding(Vector2i posWolrd, short _type)
	{
		tiles[posWolrd.x + posWolrd.y * worldSize.x].ground = &groundSprites[2];// new Building(L"Budynek", L"Opis", groundSprites[IRON]);
		tiles[posWolrd.x + posWolrd.y * worldSize.x].groundType = WOOD;
	}

	Vector2i GetSize()
	{
		return worldSize;
	}
private:
	Texture groundTexture[3];
	Sprite* groundSprites = nullptr;

	Vector2i worldSize = {0,0};
	Tile* tiles = nullptr;
};
