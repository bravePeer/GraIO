#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

enum UNIT_BULDING
{	// 0		1		2		3
	BARRACKS, WINDMILL, MINE, SAWMILL
};

class Building
{
public:
	Building()
	{}
	Building(short _type)
		:type(_type)
	{
		name = L"Budynek testowy";
		desc = L"Opis";

	}
	Building(String _name, String _desc, Sprite *_sprite)
		:name(_name), desc(_desc), sprite(_sprite)
	{

	}
	~Building()
	{
	}

	virtual void Render(RenderTarget* target)
	{

	}

	void Build();
private:
	String name;
	String desc;
	Sprite* sprite;
	unsigned int wood_cost;
	unsigned int iron_cost;
	unsigned int gold_cost;
	unsigned int stone_cost;
	int size;



	short type;
};

class Barracks
{
public:
	void madeUnit();
private:

};

class Windmill
{
public:
	void addBread();
private:

};

class Mine
{
public:
	void addStone();
	void addIron();
private:

};

class Sawmill
{
public:
	void addWood();
private:

};