#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "building.h"
#include "utilities.h"

#define TILEH	128
#define TILEW	256

using namespace std;
using namespace sf;

enum UNIT_TYPE
{
	KNIGHT, HUSSAR, ARCHER, CROSSBOWMAN
};



class Unit
{
public:
	Unit()
	{
	
		sprite = nullptr;
		actionsToDo = 0;
		alive = false;
		String name = L"";
		String desc = L"";
		int dmg = 0;
		int hp = 0;
	}
	Unit(unsigned short _type, Sprite* _sprite, short _ownerid = -1, int _hp = -1, int _lvl = 1)
		:profession(_type),sprite(_sprite), ownerid(_ownerid)
	{
		maxMoveDistance = 10;
		actionsToDo = 2;
		alive = true;

		switch (profession)
		{
		case KNIGHT://dokoksi³em go na czas testów
			name = L"Rycerz";
			desc = L"jednostka walcz¹ca w zwarciu";

			dmg = 200;
			hp = 60;
			max_hp = 60;
			move_r = 3;
			melee = 1;
			alive = 1;
			lvl = 1;
			exp = 0;

			cost.food = 20;
			cost.wood = 10;
			cost.gold = 30;
			cost.iron = 20;

			break;

		case HUSSAR:
			name = L"Husarz";
			desc = L"wzmocniona jednostka walcz¹ca w zwarciu";

			dmg = 30;
			hp = 90;
			max_hp = 90;
			move_r = 4;
			melee = 1;
			alive = 1;
			lvl = 1;
			exp = 0;

			cost.food = 30;
			cost.wood = 15;
			cost.gold = 40;
			cost.iron = 35;

			break;

		case ARCHER:
			name = L"£ucznik";
			desc = L"jednostka walcz¹ca na odleg³oœæ";

			dmg = 25;
			hp = 40;
			max_hp = 40;
			move_r = 2;
			melee = 1;
			alive = 1;
			lvl = 1;
			exp = 0;

			cost.food = 15;
			cost.wood = 10;
			cost.gold = 25;
			cost.iron = 15;

			break;

		case CROSSBOWMAN:
			name = L"Kusznik";
			desc = L"wzmocniona jednostka walcz¹ca na odleg³oœæ";

			dmg = 35;
			hp = 55;
			max_hp = 55;
			move_r = 3;
			melee = 1;
			alive = 1;
			lvl = 1;
			exp = 0;

			cost.food = 25;
			cost.wood = 20;
			cost.gold = 25;
			cost.iron = 30;

			break;
			
		}

		if (_hp > -1)
			hp = _hp;
		lvl = _lvl;
	}
	~Unit();
	void attack(Unit* enemy);
	void attack(Building* building)
	{
		building->SetDurbality(building->GetDurbility() - dmg);
		if (building->IsDestroyed())
		{
			exp += 100;
		}
	}
	void rest();
	bool isAlive();
	void lvlUp();
	void setProf();


	//-----------
	String GetName()
	{
		return name;
	}
	String GetDesc()
	{
		return desc;
	}
	String GetHPS()
	{
		return to_wstring(hp) + " / " + to_wstring(max_hp);
	}
	InGameResources* GetCost()
	{
		return &cost;
	}
	unsigned short GetType()
	{
		return profession;
	}
	int GetHp()
	{
		return hp;
	}
	int GetLvl()
	{
		return lvl;
	}

	void Render(RenderTarget* target, Vector2f pos)
	{
		sprite->setPosition(pos);
		target->draw(*sprite);
	}

	unsigned short GetMaxMoveDistance()
	{
		return maxMoveDistance;
	}
	unsigned short GetMaxAttackDistance()
	{
		return maxAttackDistance;
	}

	void SetCanDoAction(unsigned short can)
	{
		actionsToDo = can;
	}
	bool GetCanDoAction()
	{
		return actionsToDo;
	}

	short GetOwner()
	{
		return ownerid;
	}

private:
	String name;
	String desc;
	int dmg;
	int hp;
	int max_hp;
	int move_r;
	bool melee;
	bool alive;
	int lvl;
	int exp;

	InGameResources cost;
	//bool isPlayerUnit;	// czy to jednostka gracza
	short ownerid;//player id
	unsigned short profession;
	Sprite* sprite;

	unsigned short maxMoveDistance;	//maksymalna odleglosc na jaka moze ruszyc sie jednostka
	unsigned short maxAttackDistance;	//maksymalny odleglosc miedzy jednostkami by zaatakowac
	unsigned short actionsToDo;
};

Unit::~Unit()
{

}

void Unit::setProf()
{
	if (KNIGHT) //input ze rycerz
	{
		profession = 1;
	}

	if (HUSSAR) // input ze husarz
	{
		profession = 2;
	}
	
	if (ARCHER) // input ze ³ucznik
	{
		profession = 3;
	}
	
	if (CROSSBOWMAN) // input ze kusznik
	{
		profession = 4;
	}
}

bool Unit::isAlive()
{
	if (hp > 0)
	{
		alive = true;
	}
	else
	{
		alive = false;
		//usuniecie jej z mapy
	}
	return alive;
}

void Unit::attack(Unit* enemy)
{
	//if (true)//jeœli s¹ na kratkê od siebie
	//{
		if (melee == false)
		{
			enemy->hp -= dmg;
			enemy->isAlive();
			if (enemy->alive == false)
			{
				exp += 50;
			}
		}

		if (melee == true)
		{
			enemy->hp -=  dmg;
			hp = hp - (enemy->dmg * 0.5);
			isAlive();
			enemy->isAlive();
			if (enemy->alive == false)
			{
				exp += 50;
			}
		}
	//}
	
}

void Unit::rest()
{
	if (hp <= 0.5 * max_hp)
	{
		hp = hp + (0.25 * max_hp);
	}
	else
	{
		hp = hp + (0.1 * max_hp);
	}
}

void Unit::lvlUp()
{
	if (lvl == 1)
	{
		if (exp > 100)
		{
			lvl = 2;
			exp = exp - 100;
		}

	}

	if (lvl == 2)
	{
		if (exp > 200)
		{
			lvl = 3;
			exp = exp - 200;
		}
	}

	if (lvl == 3)
	{
		exp = 0; //max lvl dla jednostki
	}
}
