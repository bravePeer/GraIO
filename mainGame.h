#pragma once
#include <SFML/Graphics.hpp>
#include "unit.h"
#include "building.h"
#include "ai.h"
#include "world.h"
#include "gui.h"
#include "user.h"
#include <vector>

using namespace sf;



class Player
{
public:
	Player()
	{
		units = nullptr;
		world = nullptr;
		//units = new Unit({ 2, 2 });
	}
	Player(World* _world)
	:world(_world)
	{
		//units = new Unit(_world->GetSize());

		gameRes.food = 100;
		gameRes.gold = 100;
		gameRes.wood = 100;
		gameRes.iron = 100;

	}
	~Player()
	{
		delete units;
	}

	InGameResources GetPlayerRes()
	{
		return gameRes;
	}

	void AddUnit(Vector2i _pos)
	{
		//units = new Unit(_pos);
		//world->AddUnit(units);
	}
	void NextRound()
	{
		for (unsigned short i = 0; i < buildings.size(); i++)
		{
			buildings[i]->NextRound(&gameRes);
		}
	}
	bool CanBuildBuilding(Building* newBuilding)
	{
		if (*newBuilding->GetCost() <= gameRes)
		{
			return true;
		}
		else
			throw "Za malo surowcow";
		return false;
	}
	void BuildBuilding(Building* newBuilding)
	{
		gameRes = gameRes - *newBuilding->GetCost();
		buildings.push_back(newBuilding);
		cout << "Budynek dodany" << endl;
	}
	void Render(RenderTarget* target)
	{
		units->Render(target);
	}
private:
	Unit* units;
	World* world;

	vector<Building*> buildings;

	InGameResources gameRes;
};

/*G³ówna gra*/
class MainGame : public State
{
public:
	MainGame()
	{
		font = nullptr;

		world = nullptr;
		view = nullptr;
		unit = nullptr;

		textBox = nullptr;
		tileInfo = nullptr;

		canDrawMouseOnMap = false;

		buttons = nullptr;

		buttonPressed = -1;
		player = nullptr;
		isPlayerRound = false;
		isNextRound = true;


		buildingGraphic = nullptr;
	}
	MainGame(Font* _font)
		:font(_font)
	{
		world = new World({ 10,10 });
		unit = new Unit({ 10,10 });
		view = new View({ 800,450 }, { 1600, 900 });
		origin = view->getCenter();
		//textBox = new TextBox( { view->getSize().x, (view->getSize().y * 0.2f) }, { 0,static_cast<float>(view->getSize().y * 0.8) }, font, L"coœ tam pisz", Color(255, 0, 0, 255), Color(255, 0, 0, 255), Color(255, 0, 0, 255));
		textBox = new TextBox({ 1600,215},{0,685 }, font, L"coœ tam pisz", Color(255, 0, 0, 255), Color(255, 0, 0, 255), Color(255, 0, 0, 255));

		worldArea.setSize({ static_cast<float>(view->getSize().x),static_cast<float>(view->getSize().y * 0.8) });
		//worldArea.setPosition(0, 0);
	
		mouseOnTileTexture.loadFromFile("Resources\\Textures\\ramka.png");
		mouseOnTile.setTexture(mouseOnTileTexture);

		//tile info
		tileInfo = new TextBox({ 100,50 }, { 0,0 }, font, L"Inormacje dotycz¹ce pola", Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0), 12);
		canDrawMouseOnMap = false;


		//Przyciski
		//buttons = new Button({ view->getSize().x * 0.2f, (view->getSize().y * 0.18f) }, { 10,static_cast<float>(view->getSize().y * 0.81) }, font, L"AWd", Color(255, 200, 0, 255), Color(235, 0, 0, 255), Color(215, 0, 0, 255));

		buttons = new Button * [ALLBUTTONS];
		buttons[BUTTONBARRACKS] = new Button({ 240,100 }, { 5,690 }, font, L"Barracks", Color(255, 200, 0, 255), Color(235, 0, 0, 255), Color(215, 0, 0, 255));
		buttons[BUTTONMINE] = new Button({ 240,100 }, { 250,690 }, font, L"Mine", Color(255, 200, 0, 255), Color(235, 0, 0, 255), Color(215, 0, 0, 255));
		buttons[BUTTONWINDMILL] = new Button({ 240,100 }, { 5,795 }, font, L"Windmill", Color(255, 200, 0, 255), Color(235, 0, 0, 255), Color(215, 0, 0, 255));
		buttons[BUTTONSAWMILL] = new Button({ 240,100 }, { 250,795 }, font, L"Sawmill", Color(255, 200, 0, 255), Color(235, 0, 0, 255), Color(215, 0, 0, 255));
		buttons[BUTTONNEXTROUND] = new Button({ 240,150 }, { 1355,690 }, font, L"Next Round", Color(255, 200, 0, 255), Color(235, 0, 0, 255), Color(215, 0, 0, 255));;
		buttons[BUTTONMENU] = new Button({ 240,50 }, { 1355,845 }, font, L"Menu", Color(255, 200, 0, 255), Color(235, 0, 0, 255), Color(215, 0, 0, 255));
		buttonPressed = -1;



		player = new Player(world);
		isPlayerRound = true;
		isNextRound = true;


		//LoadBuildingTextures
		buildingGraphic = new BuildingGraphic();
		buildingGraphic->LoadBuildingGraphic();
	}
	~MainGame()
	{
		delete textBox;
		delete tileInfo;
		delete view;
		delete world;
		//delete buttons;

		for (short i = 0; i < ALLBUTTONS; i++)
		{
			delete buttons[i];
		}
		delete[] buttons;


		delete buildingGraphic;
	}

	State* IsStateChanged();

	void LoadGame()
	{
		
	}

	void Update(RenderWindow*window, Time *elapsed)
	{
		//Obsluga klawiszy (ruch mapy)
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			offset.y = 0;

			offset.x = 1 * elapsed->asMilliseconds();
			origin.x -= offset.x;
			view->setCenter(origin);
			window->setView(*view);


			//Ustawianie pozycji
			offset.x *= -1;
			ChangeGuiPosition();
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			offset.y = 0;

			offset.x = 1 * elapsed->asMilliseconds();
			origin.x += offset.x;
			view->setCenter(origin);
			window->setView(*view);

			//Ustawianie pozycji
			//textBox->SetPostition({ textBox->GetPosition().x + offset.x ,textBox->GetPosition().y });
			ChangeGuiPosition();
		}
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			offset.x = 0;

			offset.y = 1 * elapsed->asMilliseconds();
			origin.y -= offset.y;
			view->setCenter(origin);
			window->setView(*view);

			//Ustawianie pozycji
			offset.y *= -1;
			ChangeGuiPosition();
			//textBox->SetPostition({ textBox->GetPosition().x, textBox->GetPosition().y - offset.y  });
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			offset.x = 0;
			offset.y = 1 * elapsed->asMilliseconds();
			origin.y += offset.y;
			view->setCenter(origin);
			window->setView(*view);

			//Ustawianie pozycji
			//textBox->SetPostition({ textBox->GetPosition().x, textBox->GetPosition().y + offset.y  });
			ChangeGuiPosition();
		}

		//Os³uga myszki
		MouseOnWorld(window);
		
		UpdateTileInfo(window);

		//Robi wszystko podczas nowej tury
		if (isNextRound)
		{
			player->NextRound();

			isNextRound = false;
		}

		/* Tura gracza */
		if (isPlayerRound)
		{
			//Obs³uga przycisków gui
			UpdateButtons(window);
		
		}
		else /* Tura AI */
		{

			cout << "Tura gracza" << endl;
			buttonPressed = -1;
			isPlayerRound = true;
			isNextRound = true;
		}

	
	}
	void Render(RenderTarget* target)
	{
		/*Œwiat*/

		world->Render(target);

		//unit->Render(target);
		unit->Render(target);

		/*Klikniête elementy*/
		RenderMouse(target);


		/*Pzyciski i faktyczne gui xd*/
		RenderTileInfo(target);

		textBox->Render(target);
		RenderButtons(target);

		player->Render(target);

	}
private:
	Font* font;

	World* world;
	Unit* unit;
	View*  view;
	Vector2f offset;
	Vector2f origin;


	TextBox* textBox;


	Player* player;
	bool isPlayerRound;
	bool isNextRound;
	
	/* do myszki */
	RectangleShape worldArea;
	bool canDrawMouseOnMap;
	Texture mouseOnTileTexture;
	Sprite mouseOnTile;
	Vector2i mousePosOnMap;


	/* informacje o tile */
	TextBox* tileInfo;


	/*Some*/
	Vector2i secectedWorldPos;


	/* Przyciski w gui */
	Button** buttons;
	//Button* buttons;
	unsigned short buttonPressed;


	//Dodaæ dodatkowe pod gui? 

	/* Grafiki */
	BuildingGraphic *buildingGraphic;
	enum BUTTONSID
	{
		BUTTONBARRACKS, BUTTONMINE, BUTTONWINDMILL, BUTTONSAWMILL, BUTTONNEXTROUND, BUTTONMENU, ALLBUTTONS
	};

	void BuildBuilding(Vector2i _worldPos, short _type)
	{
		//Jezeli mozna wybudowaæ

		
		Building* newBuilding = nullptr;

		//1.
		switch (_type)
		{
		case MINE:
			newBuilding = new Mine(_type, buildingGraphic->GetSpriteBuilding(_type));
			break;
		case SAWMILL:
			newBuilding = new Sawmill(_type, buildingGraphic->GetSpriteBuilding(_type));
			break;
		case WINDMILL:
			newBuilding = new Windmill(_type, buildingGraphic->GetSpriteBuilding(_type));
			break;
		case BARRACKS:
			newBuilding = new Barracks(_type, buildingGraphic->GetSpriteBuilding(_type));
			break;
		default:
			newBuilding =  new TestBuilding(_type, buildingGraphic->GetSpriteBuilding(_type));
			break;
		}


		try
		{
			if (player->CanBuildBuilding(newBuilding) && world->CanSetBuilding(_worldPos, newBuilding))
			{
				player->BuildBuilding(newBuilding);
				world->SetBuilding(_worldPos, newBuilding);

			}

		//	world->SetBuilding(_worldPos, _type, buildingGraphic->GetSpriteBuilding(_type));

		}
		catch (const char* str)
		{
			cout << str << endl;
			delete newBuilding;
		}
	}


	void ChangeGuiPosition()
	{
		textBox->Move(offset);
		//buttons->Move(offset);
		for (short i = 0; i < ALLBUTTONS; i++)
		{
			buttons[i]->Move(offset);
		}
	}
	
	void UpdateButtons(RenderWindow*window)
	{
		for (int i = 0; i < ALLBUTTONS; i++)
		{
			buttons[i]->Update(static_cast<Vector2f>(Mouse::getPosition(*window)));

			if (buttons[i]->GetButtonState() == PRESSED)
			{
				buttonPressed = i;
				textBox->SetString(L"Wybierz pozycje");
			}
		}

		if (buttonPressed == BUTTONNEXTROUND)
		{
			cout << "Tura komputera" << endl;

			isPlayerRound = false;
		}
	}
	void RenderButtons(RenderTarget*target)
	{
		//buttons->Render(target);
		for (short i = 0; i < ALLBUTTONS; i++)
		{
			buttons[i]->Render(target);
		}
	}
	
	void MouseOnWorld(RenderWindow*window)
	{
		Vector2i mousePos = Mouse::getPosition(*window);
		canDrawMouseOnMap = false;

		if (worldArea.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
		{
			Vector2i pos = Vector2i(mousePos.x % window->getSize().x, mousePos.y % window->getSize().y) - Vector2i(window->getSize().x / 2, window->getSize().y / 2);
			mousePosOnMap = Screen2Map(static_cast<Vector2i>(Vector2f(pos.x, pos.y)) + static_cast<Vector2i>(window->getView().getCenter()), { TILEW,TILEH });


			canDrawMouseOnMap = true;
			mouseOnTile.setPosition(ScreenPos(mousePosOnMap, { TILEW,TILEH }));

			/*To powinno byc w innej medodzie*/

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				switch (buttonPressed)
				{
				case BUTTONBARRACKS:
					textBox->SetString(L"Wybudowano 1");
					BuildBuilding(mousePosOnMap, BARRACKS);

					break;
				case BUTTONMINE:
					textBox->SetString(L"Wybudowano 2");
					BuildBuilding(mousePosOnMap, MINE);

					break;
				case BUTTONWINDMILL:
					textBox->SetString(L"Wybudowano 3");
					BuildBuilding(mousePosOnMap, WINDMILL);
					break;
				case BUTTONSAWMILL:
					textBox->SetString(L"Wybudowano 4");
					BuildBuilding(mousePosOnMap, SAWMILL);
					break;
				default:

					textBox->SetString(L"Wybrane pole:\nx:" + to_wstring(mousePosOnMap.x) + " y:" + to_wstring(mousePosOnMap.y));
					break;
				}
				
				buttonPressed = -1;
			}
		}
	}
	void RenderMouse(RenderTarget* target)
	{
		if (canDrawMouseOnMap)
			target->draw(mouseOnTile);
	}
	
	void UpdateTileInfo(RenderWindow* window)
	{
		tileInfo->SetPostition({
			static_cast<float>(Mouse::getPosition(*window).x) + origin.x - window->getSize().x / 2 + 50,
			static_cast<float>(Mouse::getPosition(*window).y + origin.y - window->getSize().y / 2) });
		
		String tileInfoText = L"Zawartoœæ pola:\n";
		Tile tile = *world->GetTile(mousePosOnMap);
		
			switch (tile.groundType)
			{
			case GRASS:
				tileInfoText += L"Trawa";
				break;
			case IRON:
				tileInfoText += L"Z³o¿e ¿elaza";
				break;
			case STONE:
				tileInfoText += L"Z³o¿e kamienia";
				break;
			case WOOD:
				tileInfoText += L"Las";
				break;
			default:
				tileInfoText += L"-";
				break;
			}

			
			tileInfoText += L"\nZasoby:\nFood:" + to_wstring(player->GetPlayerRes().food)
				+ L"\nIron:" + to_wstring(player->GetPlayerRes().iron)
				+ L"\nWood:" + to_wstring(player->GetPlayerRes().wood)
				+ L"\nGold:" + to_wstring(player->GetPlayerRes().gold);

			tileInfo->SetString(tileInfoText);
	}
	void RenderTileInfo(RenderTarget* target)
	{
		if (canDrawMouseOnMap)
			tileInfo->Render(target);
	}
};