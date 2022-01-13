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
	Player()
	{
		//units = nullptr;
		//world = nullptr;
		//units = new Unit({ 2, 2 });
	}
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
	~Player()
	{
		//delete units;
	}

	InGameResources GetPlayerRes()
	{
		return gameRes;
	}

	void NextRound()
	{
		for (unsigned short i = 0; i < tbuildings.size(); i++)
		{
			tbuildings[i].second->NextRound(&gameRes);
			//buildings[i]->NextRound(&gameRes);
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

	//void BuildBuilding(Building* newBuilding)
	//{
	//	gameRes = gameRes - *newBuilding->GetCost();
	//	buildings.push_back(newBuilding);
	//	cout << "Budynek dodany" << endl;
	//}
	//void ProduceUnit(Unit* unit, bool free=false)
	//{
	//	if(!free)
	//		gameRes = gameRes - *unit->GetCost();
	//	units.push_back(unit);
	//	cout << "jednostka dodana" << endl;
	//}

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

	//bool HasUnit(Vector2i pos)
	//{
	//	//if (units[0]->isAlive()==true)
	//	{
	//		isUnit = true;
	//	}
	//	//else
	//	{
	//		isUnit = false;
	//		return isUnit;
	//	}
	//
	//}

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
				tunits.erase(tunits.begin() + i);
				cout << "Usunieto jednostke";
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

	static short amountOfPlayers;
private:
	//Unit* units;
	//World* world;

	//vector<Building*> buildings;
	//vector<Unit*> units;

	//test
	vector< pair<Vector2i, Building*>> tbuildings;
	vector< pair<Vector2i, Unit*>> tunits;
	//pair<Vector2i, Unit*> simplePair;
	InGameResources gameRes;

	int amountUnit = 0;
	int amountBuilding = 0;
	int maxAmountBuilding = 10;
	int maxAmountUnit = 10;
	int id;

	bool isAI;
	//bool isUnit;
};

short Player::amountOfPlayers = 0;