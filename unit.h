#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "building.h"
#include "world.h"
#include "utilities.h"

#define TILEH	128
#define TILEW	256

using namespace std;
using namespace sf;

enum UNIT_TYPE
{
	RYCERZ, HUSARZ, LUCZNIK, KUSZNIK
};

class Unit
{
public:
	Unit(Vector2i _worldSize);
	~Unit();
	void move();
	void attack(Unit enemy);
	void rest();
	void isAlive();
	void lvlUp();
	void setProf();

	Tile GetTile(Vector2i posWolrd)
	{
		return tiles[posWolrd.x + posWolrd.y * worldSize.x];
	}

	void Render(RenderTarget* target)
	{
		for (int i = 0; i < worldSize.x; i++)
		{
			for (int j = 0; j < worldSize.y; j++)
			{
				tiles[i + j * worldSize.x].unit->setPosition(ScreenPos({ i,j + 200 }, { TILEW,TILEH }));

				target->draw(*tiles[i + j * worldSize.x].unit);
			}
		}
	}

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
	Texture unitTexture[4];
	Sprite* unitSprites = nullptr;
	Vector2i worldSize = { 0,0 };
	Tile* tiles = nullptr;

};

Unit::Unit(Vector2i _worldSize)
{
	unitTexture[0].loadFromFile("Resources\\Textures\\Unit\\rycerz.png");
	unitTexture[1].loadFromFile("Resources\\Textures\\Unit\\rycerz.png");
	unitTexture[2].loadFromFile("Resources\\Textures\\Unit\\rycerz.png");
	unitTexture[3].loadFromFile("Resources\\Textures\\Unit\\rycerz.png");

	unitSprites = new Sprite[3];

	unitSprites[0].setTexture(unitTexture[0]);
	unitSprites[1].setTexture(unitTexture[1]);
	unitSprites[2].setTexture(unitTexture[2]);
	worldSize = _worldSize;

	tiles = new Tile[worldSize.x * worldSize.y];
	for (int i = 0; i < worldSize.x; i++)
	{
		for (int j = 0; j < worldSize.y; j++)
		{
			tiles[i + j * worldSize.x].unit = &unitSprites[0];
			tiles[i + j * worldSize.x].unitType = RYCERZ;
		}
	}

	tiles[4].unit = &unitSprites[0];
	tiles[4].unitType = RYCERZ;

	alive = true;
	lvl = 1;
	exp = 0;
	setProf();
	if (profession==1) //switch , enum
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
