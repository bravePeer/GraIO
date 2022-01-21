#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

/*Grafiki do gry*/
class GraphicAll
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
		cout << "Ground Textures Loaded" << endl;
	}
	void LoadBuildingGraphic()
	{
		cout << "Loading building textures" << endl;


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
		cout << "Building Textures Loaded" << endl;
	}
	void LoadUnitGraphic()
	{
		cout << "Loading Unit textures" << endl;


		unitTexture.loadFromFile("Resources\\Textures\\Unit\\units.png");
		for (int i = 0; i < 4; i++)
		{
			unitsSprite[i].setTexture(unitTexture);
			unitsSprite[i].setTextureRect(IntRect(Vector2i(256 * i, 0), Vector2i(256, 256)));
		}

		isUnitGraphicLoaded = true;
		cout << "Unit Textures Loaded" << endl;
	}

	void LoadOtherGraphic()
	{
		 mouseOnTileTexture.loadFromFile("Resources\\Textures\\Gui\\ramka.png");
		 mouseOnTileSprite.setTexture(mouseOnTileTexture);
		 isOtherGraphicsLoaded = true;
	}

	bool IsGraphicLoaded()
	{
		return isBuildingGraphicLoaded && isUnitGraphicLoaded && isTileGraphicLoaded;
	}
	Sprite* GetSpriteGround(unsigned short id)
	{
		return &tileSprite[id];
	}
	Sprite* GetAllSpritesGround()
	{
		return tileSprite;
	}

	Sprite* GetSpriteBuilding(unsigned short id)
	{
		return &buildingsSprite[id];
	}
	Sprite* GetSpriteBuildingOnTile(unsigned short id)
	{
		return &buildingsSpriteOnTile[id];
	}
	Sprite* GetSpriteUnit(unsigned short id = 0)
	{
		return &unitsSprite[id];
	}
	
	Sprite* GetSpriteMouseOnTile()
	{
		return &mouseOnTileSprite;
	}

private:
	bool isTileGraphicLoaded;
	Texture tileTexture;
	Sprite tileSprite[4];

	bool isBuildingGraphicLoaded;
	Texture buildingTexture;
	Texture buildingTexture2;
	Sprite buildingsSprite[5];
	Sprite buildingsSpriteOnTile[5];
	
	bool isUnitGraphicLoaded;
	Texture unitTexture;
	Sprite unitsSprite[4];

	bool isGuiGraphicLoaded;
	Texture guiTexture;

	bool isOtherGraphicsLoaded;
	Texture mouseOnTileTexture;
	Sprite mouseOnTileSprite;
};

/*Grafiki do menu i fonty*/
class Resources
{
public:
	void LoadResources()
	{
		texboxTexture.loadFromFile("Resources\\Textures\\Gui\\resourcesTextBoxTexture.png");
		buttonTexture.loadFromFile("Resources\\Textures\\Gui\\Frame.png");
		buttonSpecificTexture.loadFromFile("Resources\\Textures\\Gui\\menu_nextRoundTexture.png");
		mainTextBox.loadFromFile("Resources\\Textures\\Gui\\mainTextBox.png");
		font.loadFromFile("Resources\\Fonts\\comic.ttf");

	}


	Texture* GetTextBoxTexture()
	{
		return &texboxTexture;
	}

	Texture* GetButtonTexture()
	{
		return &buttonTexture;
	}
	Texture* GetButtonSpecificTexture()
	{
		return &buttonSpecificTexture;
	}
	Texture* GetMainTextBoxTexture()
	{
		return &mainTextBox;
	}

	Font* GetFont()
	{
		return &font;
	}

private:
	Texture texboxTexture;
	Texture buttonTexture;
	Texture buttonSpecificTexture;
	Texture mainTextBox;
	Font font;
};