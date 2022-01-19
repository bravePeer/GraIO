#pragma once
#include <SFML/Graphics.hpp>
#include "utilities.h"
#include "unit.h"
#include "building.h"
#include "player.h"

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
	short ownerid = -1; //playerid
	//Player* owner;
	//unsigned int buildingType = NOTHING;
	//unsigned int unitType = NOTHING;
	Vector2i size = { 1,1 };
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
	World(Vector2i _worldSize, fstream *preset, Sprite* groundSprites, short presetid)
	{
		presetId = presetid;

		colorEnemyArea.r = 255;
		colorEnemyArea.g = 0;
		colorEnemyArea.b = 0;
		colorEnemyArea.a = 200;

		colorPlayerArea.r = 0;
		colorPlayerArea.g = 255;
		colorPlayerArea.b = 255;
		colorPlayerArea.a = 200;

		colorDefaultArea.r = 255;
		colorDefaultArea.g = 255;
		colorDefaultArea.b = 255;
		colorDefaultArea.a = 255;

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
					tiles[i + j * worldSize.x].ownerid = 0;
					break;
				case 'e'://zamek przeciwnika
					tiles[i + j * worldSize.x].ground = &groundSprites[0];
					tiles[i + j * worldSize.x].groundType = GRASS;
					tiles[i + j * worldSize.x].ownerid = 1;
					break;
				case 'n':
					tiles[i + j * worldSize.x].ground = &groundSprites[0];
					tiles[i + j * worldSize.x].groundType = GRASS;
					tiles[i + j * worldSize.x].ownerid = 1;
					break;
				case 'm':
					tiles[i + j * worldSize.x].ground = &groundSprites[0];
					tiles[i + j * worldSize.x].groundType = GRASS;
					tiles[i + j * worldSize.x].ownerid = 0;
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
		delete areaSprite;
	}

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

				if (showPlayerArea)
				{
					if (tiles[i + j * worldSize.x].ownerid == 0)
					{
						areaSprite->setColor(colorPlayerArea);
						areaSprite->setPosition(ScreenPos({ i,j }, { TILEW,TILEH }));
						target->draw(*areaSprite);
					}
					else if (tiles[i + j * worldSize.x].ownerid > 0)
					{
						areaSprite->setColor(colorEnemyArea);
						areaSprite->setPosition(ScreenPos({ i,j }, { TILEW,TILEH }));
						target->draw(*areaSprite);

					}
				}

				if (tiles[i + j * worldSize.x].building)
					tiles[i + j * worldSize.x].building->Render(target, ScreenPos({ i,j }, { TILEW,TILEH }));
				if (tiles[i + j * worldSize.x].unit)
					tiles[i + j * worldSize.x].unit->Render(target, ScreenPos({ i,j }, { TILEW,TILEH }));
			}
		}
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
	void MoveUnit(Vector2i selectedUnitPos,Vector2i endPos, String *info, short _playerid, Player*player)
	{
		if (GetTile(selectedUnitPos)->unit)
		{
		//	if (!GetTile(selectedUnitPos)->unit->GetCanDoAction())
		//		throw L"Jednostka juz wykonala ruch w tej turze";

			if (!(endPos <= selectedUnitPos + GetTile(selectedUnitPos)->unit->GetMaxMoveDistance()
				&& endPos >= selectedUnitPos - GetTile(selectedUnitPos)->unit->GetMaxMoveDistance()))
				throw L"Jednostka nie moze sie ruszyc tak daleko";

			//if can move on tile
			if (!GetTile(endPos)->unit)	// Po prostu przejdz na dane pole
			{
				if (GetTile(endPos)->building)
				{
					if(!player->HasBuildingOnPos(endPos))
					//if (!GetTile(endPos)->building->IsPlayerBuilding())
						throw L"Nie mo¿na wejœæ do budynku przeciwnika";
				}
				GetTile(endPos)->unit = GetTile(selectedUnitPos)->unit;
				GetTile(selectedUnitPos)->unit = nullptr;
			}
			else
			{
				//if (GetTile(endPos)->unit->GetOwner() == _playerid)
				if(player->HasUnitOnPos(endPos))
				{
					//zajête
					throw L"Pole zajête przez sojusznicz¹ jednostke";
				}
				else
					throw L"Pole zajête przez przeciwnika";
			}
		}
		else
			throw L"Jednostka nie zosta³a wybrana";
	}
	void AttackUnit(Vector2i selectedUnitPos, Vector2i endPos, String* info,Player*player, bool *anyDestroied)
	{
		if (absVector2i(endPos - selectedUnitPos) < Vector2i(2, 2))
		{
			if (GetTile(endPos)->unit)
			{
				if (player->HasUnitOnPos(endPos))
					throw L"Nie mozna zaatakowac sojuszniczej jednostki!";

				GetTile(selectedUnitPos)->unit->attack(GetTile(endPos)->unit);
				*info = (L"Zaatakowano jednostkê [..]\nZosta³o: " + to_wstring(GetTile(selectedUnitPos)->unit->GetHp()) + L" hp\nPrzeciwnikowi zosta³o: " + to_wstring(GetTile(endPos)->unit->GetHp()) + L" hp");
				if (GetTile(selectedUnitPos)->unit->GetHp() <= 0)
				{
					DeleteUnit(selectedUnitPos);
					*info = L"Sojusznicza jednostka zosta³a zniszczona przeciwnika";
					*anyDestroied = true;
				}
				if (GetTile(endPos)->unit->GetHp() <= 0)
				{
					DeleteUnit(endPos);
					*info = L"Pokonano przeciwnika";
					*anyDestroied = true;
				}
				return;
			}

			if (GetTile(endPos)->building)
			{
				if (player->HasBuildingOnPos(endPos))
					throw L"Nie mozna zaatakowac sojuszniczego budynku!";

				*info = L"Zaatakowano budynek [...]";
				GetTile(selectedUnitPos)->unit->attack(GetTile(endPos)->building);
				if (GetTile(endPos)->building->IsDestroyed())
				{
					DeleteBuilding(endPos);
					*info = L"Zniszczono budynek przeciwnika";
					*anyDestroied = true;
				}
			}
		}
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
	void DeleteUnit(Vector2i pos)
	{
		if (GetTile(pos)->unit)
		{
			//delete GetTile(pos)->unit;
			GetTile(pos)->unit = nullptr;
		}
		else
			throw L"Nie wybrano jednostki";
	}
	void DeleteBuilding(Vector2i pos)
	{
		if (GetTile(pos)->building)
		{
			//delete GetTile(pos)->building;
			GetTile(pos)->building = nullptr;
		}
		else
			throw L"Nie wybrano budynku";
	}

	void IncreaseArea(short playerid, Vector2i pos = {-1,-1})
	{
		if (pos.x == -1) // losowe
		{
			vector<Vector2i> addTileToArea;
			for (int i = 0; i < worldSize.x; i++)
			{
				for (int j = 0; j < worldSize.y; j++)
				{
					if (tiles[i + j * worldSize.x].ownerid == playerid)
					{
						if (tiles[i - 1 + j * worldSize.x].ownerid == -1)
						{
							if(((i-1) + j  * worldSize.x)/ worldSize.x == j)
							addTileToArea.push_back({ i - 1 , j });
						}
						else if (tiles[i + 1 + j * worldSize.x].ownerid == -1)
						{
							if (((i + 1) + j * worldSize.x) / worldSize.x == j)
								addTileToArea.push_back({ i + 1 , j });
						}
						else if (tiles[i + (j + 1) * worldSize.x].ownerid == -1)
						{
								addTileToArea.push_back({ i  , j+1 });
						}
						else if (tiles[i + (j - 1) * worldSize.x].ownerid == -1)
						{
								addTileToArea.push_back({ i , j-1 });
						}
						else
							continue;
					}
				}
			}

			if (addTileToArea.size() > 0)
			{
				int a = rand() % addTileToArea.size();
				tiles[addTileToArea[a].x + addTileToArea[a].y * worldSize.x].ownerid = playerid;

			}
		}
		else // wybrana pozycja
		{

		}
	}
	
	void SetAreaSprite(Sprite *_areaSprite)
	{
		temp.loadFromFile("Resources\\Textures\\ramka.png");
		areaSprite = new Sprite();
		areaSprite->setTexture(temp);
		//areaSprite = _areaSprite;
	}
	

	bool CanSetBuilding(Vector2i posWolrd, Building* _building,short playerid)
	{
		if (tiles[posWolrd.x + posWolrd.y * worldSize.x].unit)
		{
			throw L"Nie mozna wybudowac budynku\nz powodu przeszkadzaj¹cej jednostki";
		}

	 	if (tiles[posWolrd.x + posWolrd.y * worldSize.x].ownerid != playerid)
		 	throw L"To pole nie nale¿y do ciebie!";

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
	bool CanSetUnit(Vector2i posWolrd, Unit* unit)
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
	short GetUsedPresetId()
	{
		return presetId;
	}

	/*Za³adowanie budynków i jednostek do mapy z save*/
	void SetLoadedUnitsBuildings(Player*player)
	{
		  vector< pair<Vector2i, Building*>>* tbuildings = player->GetPointerOnBuildings();
		  vector< pair<Vector2i, Unit*>>* tunits = player->GetPointerOnUnits();

		for (int i = 0; i < tbuildings->size(); i++)
		{
			SetBuilding((*tbuildings)[i].first, (*tbuildings)[i].second);
		}

		for (int  i = 0; i < tunits->size(); i++)
		{
			SetUnit((*tunits)[i].first, (*tunits)[i].second);
		}

	}
	void SavePlayerArea(fstream* save,int playerId)
	{
		*save << "A ";
		for (int i = 0; i < worldSize.x * worldSize.y; i++)
		{
			if (tiles[i].ownerid == playerId)
				*save << i << ' ';
		}
		*save << 'E'<<endl;
	}
	void LoadPlayerArea(fstream* save, int playerId)
	{
		string buf;
		*save >> buf;
		if (buf == 'A')
		{
			while (1)
			{
				*save >> buf;
				if (buf == 'E')
					break;
				tiles[stoi(buf)].ownerid = playerId;
			}
		}

	}
private:
	//Texture groundTexture[3];
	//Sprite* groundSprites = nullptr;
	bool showPlayerArea = true;

	Vector2i worldSize = { 0,0 };
	Tile* tiles = nullptr;
	
	Texture temp;
	Sprite* areaSprite;
	Color colorPlayerArea;
	Color colorEnemyArea;
	Color colorDefaultArea;

	short presetId;
};
