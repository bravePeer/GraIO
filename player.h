#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include "unit.h"
#include "building.h"
#include "ai.h"
#include "world.h"
#include "gui.h"
#include "user.h"
using namespace sf;

class Player
{
public:
	Player(bool _isAI)
		:isAI(_isAI)
	{
		gameRes.food = 100;
		gameRes.gold = 100;
		gameRes.wood = 100;
		gameRes.iron = 100;

		id = amountOfPlayers;
		amountOfPlayers++;
	}
	~Player(){}

	InGameResources GetPlayerRes()
	{
		return gameRes;
	}

	void NextRound()
	{
		for (unsigned short i = 0; i < tbuildings.size(); i++)
		{
			tbuildings[i].second->NextRound(&gameRes);
		}

		for (unsigned short i = 0; i < tunits.size(); i++)
		{
			tunits[i].second->SetCanDoAction(true);
		}
	}

	bool CanBuildBuilding(Building* newBuilding)
	{
		if (amountBuilding + 1 < maxAmountBuilding)
		{
			if (*newBuilding->GetCost() <= gameRes)
			{
				return true;
			}
			else
				throw L"Za ma³o surowców";
		}
		return false;
	}
	bool CanProduceUnit(Unit* unit)
	{
		if (amountUnit + 1 < maxAmountUnit)//dodaj to i moze blad zniknie xd
		{
			if (*unit->GetCost() <= gameRes)
				return true;
			else
				throw L"Za ma³o surowców";
		}
		return false;
	}

	Vector2i GetBuildingArea()
	{

	}

	void BuildBuilding(Building* newBuilding, Vector2i pos)
	{
		gameRes = gameRes - *newBuilding->GetCost();
		tbuildings.push_back(make_pair(pos, newBuilding));
		amountBuilding++;
		cout << "Budynek dodany" << endl;
	}
	void ProduceUnit(Unit* unit, Vector2i pos, bool free = false)
	{
		if (!free)
			gameRes = gameRes - *unit->GetCost();
		tunits.push_back(make_pair(pos, unit));
		amountUnit++;
		cout << "jednostka dodana" << endl;
	}

	bool IsAI()
	{
		return isAI;
	}


	int GetAmountOfUnit(short type = -1)
	{
		int amount = 0;
		for (int i = 0; i < tunits.size(); i++)
		{
			if (tunits[i].second->GetType() == type || type == -1)
				amount++;
		}
		return amount;
	}
	Vector2i GetPosOfUnit(short type = -1, int number = 0)
	{
		int n = 0;
		for (int i = 0; i < tunits.size(); i++)
		{
			if (tunits[i].second->GetType() == type || type == -1)
			{
				if (n == number)
					return tunits[i].first;
				else
					n++;
			}
		}
		return { -1,-1 };
	}

	int GetAmountOfBuilding(unsigned short type)
	{
		int amount = 0;
		for (int i = 0; i < tbuildings.size(); i++)
		{
			if (tbuildings[i].second->GetType() == type)
				amount++;
		}
		return amount;
	}
	Vector2i GetPosOfBuilding(unsigned short type, int number = 0)
	{
		int n = 0;
		for (int i = 0; i < tbuildings.size(); i++)
		{
			if (tbuildings[i].second->GetType() == type)
			{
				if (n == number)
					return tbuildings[i].first;
				else
					n++;
			}
		}
		return { -1,-1 };
	}
	bool HasBuildingOnPos(Vector2i pos)
	{
		for (int i = 0; i < tbuildings.size(); i++)
		{
			if (tbuildings[i].first == pos)
				return true;
		}
		return false;
	}
	bool HasUnitOnPos(Vector2i pos)
	{
		for (int i = 0; i < tunits.size(); i++)
		{
			if (tunits[i].first == pos)
				return true;
		}
		return false;
	}

	void UpdateUnitPos(Vector2i oldpos, Vector2i newpos)
	{
		for (int i = 0; i < tunits.size(); i++)
		{
			if (tunits[i].first == oldpos)
			{
				tunits[i].first = newpos;
				tunits[i].second->SetCanDoAction(false);
				return;
			}
		}
	}
	
	void UpdateDeletedUnits()
	{
		for (int i = 0; i < tunits.size(); i++)
		{
			if (!tunits[i].second->isAlive())
			{
				delete tunits[i].second;
				tunits.erase(tunits.begin() + i);
				cout << "Usunieto jednostke";
			}
		}
	}
	void UpdateDeletedBuildings()
	{
		for (int i = 0; i < tbuildings.size(); i++)
		{
			if (tbuildings[i].second->IsDestroyed())
			{
				delete tbuildings[i].second;
				tbuildings.erase(tbuildings.begin() + i);
				cout << "Usunieto budynek";
			}
		}
	}

	void Render(RenderTarget* target)
	{
		//	units->Render(target);
	}

	short GetId()
	{
		return id;
	}

	/*---Zapisywanie i wczytywanie gry---*/
	void SavePlayer(fstream* save)
	{
		//Zapisuje stan "skarbca"
		*save << id<<endl;
		*save << gameRes.food << ' ' << gameRes.gold << ' ' << gameRes.iron << ' ' << gameRes.wood << endl;

		//Zapisuje budynki
		*save << tbuildings.size()<<endl;
		for (int i = 0; i < tbuildings.size(); i++)
		{
			*save << tbuildings[i].first.x <<' '<< tbuildings[i].first.y << ' ' << tbuildings[i].second->GetType() << ' ' << tbuildings[i].second->GetDurbility() << endl;
		}

		//Zapisuje jednostki
		*save << tunits.size() << endl;
		for (int i = 0; i < tunits.size(); i++)
		{
			*save << tunits[i].first.x << ' ' << tunits[i].first.y << ' ' << tunits[i].second->GetType() << ' ' << tunits[i].second->GetHp() << ' ' << tunits[i].second->GetLvl() << endl;
		}
	}
	void LoadPlayer(fstream* save, GraphicAll*graphicAll)
	{
		int size, type, hp, buf;
		Vector2i pos;
		*save >> id;	//id gracza
		*save >> gameRes.food >> gameRes.gold >> gameRes.iron >> gameRes.wood;

		*save >> size;//liczbe budynkow
		for (int i = 0; i < size; i++)
		{
			*save >> pos.x >> pos.y >> type >> hp;
			switch (type)
			{
			case BARRACKS:
				tbuildings.push_back(make_pair(pos, new Barracks(BARRACKS, graphicAll->GetSpriteBuilding(BARRACKS), isAI, hp)));
					break;
			case WINDMILL:
				tbuildings.push_back(make_pair(pos, new Windmill(WINDMILL, graphicAll->GetSpriteBuilding(WINDMILL), isAI, hp)));
				break;
			case SAWMILL:
				tbuildings.push_back(make_pair(pos, new Barracks(SAWMILL, graphicAll->GetSpriteBuilding(SAWMILL), isAI, hp)));
				break;
			case MINE:
				tbuildings.push_back(make_pair(pos, new Barracks(MINE, graphicAll->GetSpriteBuilding(MINE), isAI, hp)));
				break;
			case CASTLE:
				tbuildings.push_back(make_pair(pos, new Barracks(CASTLE, graphicAll->GetSpriteBuilding(CASTLE), isAI, hp)));
				break;
			default:
				break;
			}
		}

		//Wczytywanie jednostek
		*save >> size;
		for (int i = 0; i < size; i++)
		{
			*save >> pos.x >> pos.y >> type >> hp >> buf;
			tunits.push_back(make_pair(pos, new Unit(type, graphicAll->GetSpriteUnit(type), id, hp, buf)));
		}
	}
	vector< pair<Vector2i, Unit*>>* GetPointerOnUnits()
	{
		return &tunits;
	}
	vector< pair<Vector2i, Building*>>* GetPointerOnBuildings()
	{
		return &tbuildings;
	}

	static short amountOfPlayers;
private:

	//test
	vector< pair<Vector2i, Building*>> tbuildings;
	vector< pair<Vector2i, Unit*>> tunits;
	InGameResources gameRes;

	int amountUnit = 0;
	int amountBuilding = 0;
	int maxAmountBuilding = 10;
	int maxAmountUnit = 10;
	int id;

	bool isAI;
};

short Player::amountOfPlayers = 0;