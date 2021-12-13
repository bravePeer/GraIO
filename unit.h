#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "building.h"

using namespace std;
using namespace sf;

class Unit
{
public:
	Unit();
	~Unit();
	void move();
	void attack(Unit enemy);
	void rest();
	void isAlive();
	void lvlUp();
	void setProf();

private:
	string name;
	int dmg;
	int hp;
	int max_hp;
	int move_r;
	bool melee;
	bool alive;
	int lvl;
	int exp;
	int profession; //1-rycerz, 2-husarz, 3-³ucznik, 4-kusznik

};

Unit::Unit()
{
	alive = true;
	lvl = 1;
	exp = 0;
	setProf();
	if (profession==1) 
	{
		melee = true;
		name = "Rycerz";
		dmg = 20;
		max_hp = 60;
		hp = max_hp;
		move_r = 3;
	}

	if (profession == 2)
	{
		melee = true;
		name = "Husarz";
		dmg = 30;
		max_hp = 90;
		hp = max_hp;
		move_r = 4;
	}

	if (profession == 3) 
	{
		melee = true;
		name = "Lucznik";
		dmg = 25;
		max_hp = 40;
		hp = max_hp;
		move_r = 2;
	}

	if (profession == 4) 
	{
		melee = true;
		name = "Kusznik";
		dmg = 30;
		max_hp = 50;
		hp = max_hp;
		move_r = 3;
	}
}

Unit::~Unit()
{

}

void Unit::setProf()
{
	if (true) //input ze rycerz
	{
		profession = 1;
	}

	if (true) // input ze husarz
	{
		profession = 2;
	}
	
	if (true) // input ze ³ucznik
	{
		profession = 3;
	}
	
	if (true) // input ze kusznik
	{
		profession = 4;
	}
}

void Unit::move()
{
	//poruszanie sie
}

void Unit::isAlive()
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
}

void Unit::attack(Unit enemy)
{
	if (true)//jeœli s¹ na kratkê od siebie
	{
		if (melee == false)
		{
			enemy.hp = enemy.hp - dmg;
			enemy.isAlive();
			if (enemy.alive == false)
			{
				exp += 50;
			}
		}

		if (melee == true)
		{
			enemy.hp = enemy.hp - dmg;
			hp = hp - (enemy.dmg * 0, 5);
			isAlive();
			enemy.isAlive();
			if (enemy.alive == false)
			{
				exp += 50;
			}
		}
	}
	
}

void Unit::rest()
{
	if (hp <= 0, 5 * max_hp)
	{
		hp = hp + (0, 25 * max_hp);
	}

	else
	{
		hp = hp + (0, 1 * max_hp);
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