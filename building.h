#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

enum BUILDINGTYPES
{
	BARRACKS, MINE, WINDMILL,SAWMILL, CASTLE
};

class BuildingGraphic
{
public:
	void LoadBuildingGraphic()
	{
		cout << "Loading textures" << endl;


		buildingTexture.loadFromFile("Resources\\Textures\\Building\\Buildings.png");
		for (int i = 0; i < 5; i++)
		{
			buildingsSprite[i].setTexture(buildingTexture);
			buildingsSprite[i].setTextureRect(IntRect(Vector2i(256 * i, 0), Vector2i(256, 256)));
		}

		isBuildingGraphicLoaded = true;
		cout << "Textures Loaded" << endl;
	}

	bool IsBuildingGraphicLoaded()
	{
		return isBuildingGraphicLoaded;
	}
	Sprite* GetSpriteBuilding(unsigned short id)
	{
		return &buildingsSprite[id];
	}
private:
	bool isBuildingGraphicLoaded;

	Texture buildingTexture;
	Sprite buildingsSprite[5];
};


class Building
{
public:
	Building()
	{}
	Building(short _type, Sprite* _sprite, bool is = false)
		:type(_type)
	{
		name = L"Budynek brak";
		desc = L"Opis";
		isPlayerBuilding = is;
	}
	Building(String _name, String _desc, Sprite *_sprite)
		:name(_name), desc(_desc), sprite(_sprite)
	{

	}
	~Building()
	{
	}

	//Pocz¹tek nowej tury 
	virtual void NextRound(InGameResources* playerRes)
	{
		playerRes->food += production.food;
		playerRes->gold += production.gold;
		playerRes->iron += production.iron;
		playerRes->wood += production.wood;
	}

	virtual InGameResources* GetCost()
	{
		return &cost;
	}

	virtual unsigned short GetNeededGround()
	{
		return neededGround;
	}

	virtual unsigned short GetType()
	{
		return type;
	}

	virtual String GetName()
	{
		return name;
	}

	virtual String GetDesc()
	{
		return desc;
	}

	virtual String GetNameNeededGround()
	{
		switch (neededGround)
		{
		case GROUNDTYPES::GRASS:
			return L"Trawa";
			break;
		case GROUNDTYPES::IRON:
			return L"Z³o¿e ¿elaza";
			break;
		case GROUNDTYPES::STONE:
			return L"Z³o¿e kamienia";
			break;
		case GROUNDTYPES::WOOD:
			return L"Las";
			break;
		default:
			return L" - ";
			break;
		}
	}

	bool IsPlayerBuilding()
	{
		return isPlayerBuilding;
	}

	virtual void Update()
	{

	}

	virtual void Render(RenderTarget* target, Vector2f pos)
	{
		sprite->setPosition(pos);
		target->draw(*sprite);
	}
protected:
	String name;
	String desc;
	Sprite* sprite;


	unsigned short type;
	unsigned short neededGround;
	InGameResources cost;
	InGameResources production;
	float durability;
	float maxdurability;

	bool isPlayerBuilding;
};

class TestBuilding : public Building
{
public:
	TestBuilding(short _type, Sprite* _sprite, bool is = false)
	{
		sprite = _sprite;
		type = _type;
		name = L"Budynek Testowy";
		desc = L"Przyk³adowy opis budynku testowego";
		cost.food = 0;
		cost.iron = 0;
		cost.gold = 50;
		cost.wood = 10;

		production.food = 1;
		production.iron = 1;
		production.gold = 10;
		production.wood = 30;

		neededGround = GROUNDTYPES::NOTHING;
		isPlayerBuilding = is;
	}

	//void NextRound(InGameResources* playerRes)
	//{
	//	playerRes->food += production.food;
	//	playerRes->gold += production.gold;
	//	playerRes->iron += production.iron;
	//	playerRes->wood += production.wood;
	//}

	//void Render(RenderTarget* target, Vector2f pos)
	//{
	//	sprite->setPosition(pos);
	//	target->draw(*sprite);
	//}
};

class Barracks : public Building
{
public:
	Barracks(short _type, Sprite* _sprite, bool is = false)
	{
		sprite = _sprite;
		type = _type;
		name = L"Koszary";
		desc = L"Pozwalaj¹ szkoliæ jednostki";
		cost.food = 0;
		cost.iron = 0;
		cost.gold = 50;
		cost.wood = 10;

		production.food = 1;
		production.iron = 1;
		production.gold = 10;
		production.wood = 30;
		isPlayerBuilding = is;
	}
};

class Mine : public Building
{
public:
	Mine(short _type, Sprite* _sprite, bool is = false)
	{
		sprite = _sprite;
		type = _type;
		name = L"Kopalnia";
		desc = L"Pozwala wydobywaæ surowce ze z³ó¿";
		cost.food = 0;
		cost.iron = 0;
		cost.gold = 90;
		cost.wood = 10;

		production.food = 1;
		production.iron = 1;
		production.gold = 40;
		production.wood = 30;

		neededGround = GROUNDTYPES::IRON;
		isPlayerBuilding = is;
	}
};

class Sawmill : public Building
{
public:
	Sawmill(short _type, Sprite* _sprite, bool is = false)
	{
		sprite = _sprite;
		type = _type;
		name = L"Tartak";
		desc = L"Pozyskuje drewno z lasu";
		cost.food = 0;
		cost.iron = 0;
		cost.gold = 50;
		cost.wood = 10;

		production.food = 1;
		production.iron = 1;
		production.gold = 10;
		production.wood = 30;
		isPlayerBuilding = is;
	}
};

class Windmill : public Building
{
public:
	Windmill(short _type, Sprite* _sprite, bool is = false)
	{
		sprite = _sprite;
		type = _type;
		name = L"M³yn";
		desc = L"Produkuje po¿ywienie";
		cost.food = 0;
		cost.iron = 0;
		cost.gold = 50;
		cost.wood = 10;

		production.food = 70;
		production.iron = 1;
		production.gold = 10;
		production.wood = 30;
		isPlayerBuilding = is;
	}
};

class Castle : public Building
{
	Castle(short _type, Sprite* _sprite, bool is = false)
	{
		sprite = _sprite;
		type = _type;
		name = L"Zamek";
		desc = L"G³ówny budynek, je¿eli zostanie zniszczony gracz przegrywa";
		cost.food = 0;
		cost.iron = 0;
		cost.gold = 0;
		cost.wood = 0;

		production.food = 10;
		production.iron = 10;
		production.gold = 10;
		production.wood = 10;

		durability = 100.f;
		maxdurability = durability;
		neededGround = GROUNDTYPES::NOTHING;
		isPlayerBuilding = is;
	}
};