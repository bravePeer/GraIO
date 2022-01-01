#pragma once
#include <SFML/Graphics.hpp>
#include "utilities.h"
#include "unit.h"
#include "building.h"

#define TILEH	128
#define TILEW	256

using namespace sf;



struct Tile
{
	Sprite* ground = nullptr;	// Groun* ground
	//Sprite* building = nullptr; // 
	Building* building = nullptr;
	
	Unit* unit = nullptr;
	//Sprite* unit = nullptr;		
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
		groundTexture[2].loadFromFile("Resources\\Textures\\IDK\\forest.png");
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

		tiles[1].ground = &groundSprites[2];
		tiles[10].ground = &groundSprites[2];
		tiles[11].ground = &groundSprites[2];

	
		tiles[0].groundType = IRON;
		tiles[4].groundType = IRON;
		tiles[7].groundType = IRON;

		tiles[10].groundType = WOOD;
		tiles[11].groundType = WOOD;
		tiles[1].groundType = WOOD;
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
		for (int i = 0; i < worldSize.x; i++)
		{
			for (int j = 0; j < worldSize.y; j++)
			{
				tiles[i + j * worldSize.x].ground->setPosition(ScreenPos({ i,j }, { TILEW,TILEH }));

				target->draw(*tiles[i + j * worldSize.x].ground);
				if (tiles[i + j * worldSize.x].building)
					tiles[i + j * worldSize.x].building->Render(target, ScreenPos({ i,j }, { TILEW,TILEH }));
				if (tiles[i + j * worldSize.x].unit)
					tiles[i + j * worldSize.x].unit->Render(target, ScreenPos({ i,j }, { TILEW,TILEH }));
			}
		}
	}
	/*Przestarzal¹ funkcja*/
	void SetBuilding(Vector2i posWolrd, short _type, Sprite*_sprite)
	{
		if (!tiles[posWolrd.x + posWolrd.y * worldSize.x].building)
			tiles[posWolrd.x + posWolrd.y * worldSize.x].building = new TestBuilding(_type, _sprite);
		else
			throw "Pole zajête";
		//tiles[posWolrd.x + posWolrd.y * worldSize.x].groundType = WOOD;
	}
	/*Aktualna*/
	void SetBuilding(Vector2i posWolrd, Building* _building)
	{
		tiles[posWolrd.x + posWolrd.y * worldSize.x].building = _building;
	}
	void SetUnit(Vector2i posWolrd, Unit* unit)
	{
		tiles[posWolrd.x + posWolrd.y * worldSize.x].unit = unit;
	}

	bool CanSetBuilding(Vector2i posWolrd, Building* _building)
	{
		if (!tiles[posWolrd.x + posWolrd.y * worldSize.x].building)
		{
			if (_building->GetNeededGround() == GROUNDTYPES::NOTHING)
				return true;
			else if (_building->GetNeededGround() == tiles[posWolrd.x + posWolrd.y * worldSize.x].groundType)
				return true;
			else
				throw L"Brak surowców na tym polu";
		}
		else
			throw L"Pole zajête";
		return false;
	}
	bool CanSetUnit(Vector2i posWolrd, Unit*unit)
	{
		if (!tiles[posWolrd.x + posWolrd.y * worldSize.x].unit)
		{
			return true;
		}
		else
			throw L"Pole zajête";
		return false;
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
