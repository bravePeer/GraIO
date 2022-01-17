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
		buildingTexture2.loadFromFile("Resources\\Textures\\Building\\Buildings.png");
		for (int i = 0; i < 5; i++)
		{
			buildingsSprite[i].setTexture(buildingTexture);
			buildingsSprite[i].setTextureRect(IntRect(Vector2i(256 * i, 0), Vector2i(256, 256)));
			buildingsSpriteOnTile[i].setTexture(buildingTexture2);
			buildingsSpriteOnTile[i].setTextureRect(IntRect(Vector2i(256 * i, 0), Vector2i(256, 256)));
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
	Sprite* GetSpriteBuildingOnTile(unsigned short id)
	{
		return &buildingsSpriteOnTile[id];
	}
private:
	bool isBuildingGraphicLoaded;

	Texture buildingTexture;
	Texture buildingTexture2;
	Sprite buildingsSprite[5];
	Sprite buildingsSpriteOnTile[5];
};


class Building
{
public:
	Building()
	{
		name = L"";
		desc = L"";
		durability = 0;
		maxdurability = 0;
	}
	Building(short _type, Sprite* _sprite, bool is = false)
		:type(_type)
	{
		name = L"Budynek brak";
		desc = L"Opis";
		//isPlayerBuilding = is;
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

	virtual bool IsDestroyed()
	{
		return durability <= 0 ? true : false;
	}
	virtual void SetDurbality(int _durbality)
	{
		durability = _durbality;
	}
	virtual int GetDurbility()
	{
		return durability;
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
	virtual String GetDurabilityS()
	{
		return to_wstring(durability) + " / " + to_wstring(maxdurability);
	}

	//bool IsPlayerBuilding()
	//{
	//	return isPlayerBuilding;
	//}
	
	virtual void Update()
	{

	}
	virtual void Render(RenderTarget* target, Vector2f pos)
	{
		sprite->setPosition(pos);
		target->draw(*sprite);
	}

	//Maksymalna odleg³oœæ od budynku gdzie gracz mo¿e postawiæ kolejny budynek
	//static unsigned short maxDistanceBuild;
protected:
	String name;
	String desc;
	Sprite* sprite;


	unsigned short type;
	unsigned short neededGround;
	InGameResources cost;
	InGameResources production;
	int durability;
	int maxdurability;

	//bool isPlayerBuilding;
};

//unsigned short Building::maxDistanceBuild = 5;

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
		durability = 100;
		maxdurability = durability;
		//isPlayerBuilding = is;
	}
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
		//isPlayerBuilding = is;
		durability = 100;
		maxdurability = durability;
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
		//isPlayerBuilding = is;
		durability = 100;
		maxdurability = durability;
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
		//isPlayerBuilding = is;
		durability = 100;
		maxdurability = durability;
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
		//isPlayerBuilding = is;
		durability = 100;
		maxdurability = durability;
	}
};

class Castle : public Building
{
public:
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

		durability = 500;
		maxdurability = durability;
		neededGround = GROUNDTYPES::NOTHING;
		//isPlayerBuilding = is;
	}
};