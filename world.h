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

class Graphic
{
public:
	void LoadGroundGraphic(short limit = 4)
	{
		cout << "Loading ground textures" << endl;


		tileTexture.loadFromFile("Resources\\Textures\\Ground\\grounds.png");
		for (int i = 0; i < limit; i++)
		{
			tileSprite[i].setTexture(tileTexture);
			tileSprite[i].setTextureRect(IntRect(Vector2i(256 * i, 0), Vector2i(256, 256)));
		}

		isTileGraphicLoaded = true;
		cout << "ground Textures Loaded" << endl;
	}

	bool IsGroundGraphicLoaded()
	{
		return isTileGraphicLoaded;
	}
	Sprite* GetSpriteGround(unsigned short id)
	{
		return &tileSprite[id];
	}
	Sprite* GetAllSpritesGround()
	{
		return tileSprite;
	}
private:
	Texture tileTexture;
	Sprite tileSprite[4];

	bool isTileGraphicLoaded;

};

class World
{
public:
	World()
	{}
	World(Vector2i _worldSize, Sprite*groundSprites)
	{
		//groundTexture[0].loadFromFile("Resources\\Textures\\Ground\\ground.png");
		//groundTexture[1].loadFromFile("Resources\\Textures\\Ground\\iron.png");
		//groundTexture[2].loadFromFile("Resources\\Textures\\IDK\\forest.png");
		//groundSprites = new Sprite[3];
		//
		//groundSprites[0].setTexture(groundTexture[0]);
		//groundSprites[1].setTexture(groundTexture[1]);
		//groundSprites[2].setTexture(groundTexture[2]);

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
	World(Vector2i _worldSize, fstream *preset, Sprite* groundSprites)
	{
		worldSize = _worldSize;
		tiles = new Tile[worldSize.x * worldSize.y];

		string buf;
		for (int j = 0; j < worldSize.y; j++)
		{
			*preset >> buf;
			for (int i = 0; i < worldSize.x; i++)
			{
				switch (buf[i])
				{
				case 'g'://grass
					tiles[i + j * worldSize.x].ground = &groundSprites[0];
					tiles[i + j * worldSize.x].groundType = GRASS;
					break;
				case 'i'://zelazo
					tiles[i + j * worldSize.x].ground = &groundSprites[1];
					tiles[i + j * worldSize.x].groundType = IRON;
					break;
				case 'w'://las
					tiles[i + j * worldSize.x].ground = &groundSprites[2];
					tiles[i + j * worldSize.x].groundType = WOOD;
					break;
				case 'p'://zamek gracza
					tiles[i + j * worldSize.x].ground = &groundSprites[0];
					tiles[i + j * worldSize.x].groundType = GRASS;
					break;
				case 'e'://zamek przeciwnika
					tiles[i + j * worldSize.x].ground = &groundSprites[0];
					tiles[i + j * worldSize.x].groundType = GRASS;
					break;
				}
			}
		}

	}
	~World()
	{
		//	if(groundSprites)
			//	delete groundSprites;
		for (int i = 0; i < worldSize.x * worldSize.y; i++)
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
	/*Przestarzal� funkcja*/
	void SetBuilding(Vector2i posWolrd, short _type, Sprite* _sprite)
	{
		if (!tiles[posWolrd.x + posWolrd.y * worldSize.x].building)
			tiles[posWolrd.x + posWolrd.y * worldSize.x].building = new TestBuilding(_type, _sprite);
		else
			throw "Pole zaj�te";
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
	void MoveUnit(Vector2i selectedUnitPos,Vector2i endPos,String *info, bool attack = false)
	{
		if (GetTile(selectedUnitPos)->unit)
		{
			//if can move on tile
			if (!GetTile(endPos)->unit)	// Po prostu przejdz na dane pole
			{
				if (GetTile(endPos)->building)
				{
					if (!GetTile(endPos)->building->IsPlayerBuilding())
						throw L"Nie mo�na wej�� do budynku przeciwnika";
				}
				GetTile(endPos)->unit = GetTile(selectedUnitPos)->unit;
				GetTile(selectedUnitPos)->unit = nullptr;
			}
			else
			{
				if (GetTile(endPos)->unit->IsPlayerUnit())
				{
					//zaj�te
					throw L"Pole zaj�te przez sojusznicz� jednostke";
				}
				else // walka
				{
					if (attack)
					{
						//
						//      E
						//    E U E
						//      E
						
						if (absVector2i( endPos - selectedUnitPos) < Vector2i(2, 2))
						{
							GetTile(selectedUnitPos)->unit->attack(*GetTile(endPos)->unit);
							*info = (L"Zaatakowano jednostk� [..]\nZosta�o: " + to_wstring(GetTile(selectedUnitPos)->unit->GetHp()) + L" hp\nPrzeciwnikowi zosta�o: " + to_wstring(GetTile(endPos)->unit->GetHp()) + L" hp");
							if (GetTile(selectedUnitPos)->unit->GetHp() <= 0)
							{
								DeleteUnit(selectedUnitPos);
								*info = L"Sojusznicza jednostka zosta�a zniszczona przeciwnika";

							}
							if (GetTile(endPos)->unit->GetHp() <= 0)
							{
								DeleteUnit(endPos);
								*info = L"Pokonano przeciwnika";
							}
						}
					}
					else
						throw L"Pole zaj�te przez przeciwnika";
				}
			}
		}
		else
			throw L"Jednostka nie zosta�a wybrana";
	}
	void HealUnit(Vector2i selectedUnitPos)
	{
		if (GetTile(selectedUnitPos)->unit)
		{
			GetTile(selectedUnitPos)->unit->rest();
		}
		else
			throw L"Nie wybrano jednostki";
	}
	void DeleteUnit(Vector2i selectedUnitPos)
	{
		if (GetTile(selectedUnitPos)->unit)
		{
			delete GetTile(selectedUnitPos)->unit;
			GetTile(selectedUnitPos)->unit = nullptr;
		}
		else
			throw L"Nie wybrano jednostki";
	}

	bool CanSetBuilding(Vector2i posWolrd, Building* _building)
	{
		if (tiles[posWolrd.x + posWolrd.y * worldSize.x].unit)
		{
			throw L"Nie mozna wybudowac budynku\nz powodu przeszkadzaj�cej jednostki";
		}

		if (!tiles[posWolrd.x + posWolrd.y * worldSize.x].building)
		{
			if (_building->GetNeededGround() == GROUNDTYPES::NOTHING)
				return true;
			else if (_building->GetNeededGround() == tiles[posWolrd.x + posWolrd.y * worldSize.x].groundType)
				return true;
			else
				throw L"Brak surowc�w na tym polu";
		}
		else
			throw L"Pole zaj�te";
		return false;
	}
	bool CanSetUnit(Vector2i posWolrd, Unit* unit)
	{
		if (!tiles[posWolrd.x + posWolrd.y * worldSize.x].unit)
		{
			return true;
		}
		else
			throw L"Pole zaj�te";
		return false;
	}
	
	Vector2i GetSize()
	{
		return worldSize;
	}
private:
	//Texture groundTexture[3];
	//Sprite* groundSprites = nullptr;

	Vector2i worldSize = { 0,0 };
	Tile* tiles = nullptr;
};
