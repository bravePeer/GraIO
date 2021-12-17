#pragma once
#include <SFML/Graphics.hpp>
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
		units = nullptr;
		world = nullptr;
		//units = new Unit({ 2, 2 });
	}
	Player(World* _world)
	:world(_world)
	{
		units = new Unit(_world->GetSize());
	}
	~Player()
	{
		delete units;
	}

	void CreateUnit(Vector2i _pos)
	{
		units = new Unit(_pos);
		//world->AddUnit(units);
	}
	void CreateBuilding(Vector2i _pos)
	{
	//	Tile* tile = world->GetTile(_pos);
	//	tile->building = new Building()
	}
	void Render(RenderTarget* target)
	{
		units->Render(target);
	}
private:
	Unit* units;
	World* world;
};

/*G³ówna gra*/
class MainGame : public State
{
public:
	MainGame()
	{
		world = nullptr;
		view = nullptr;
		unit = nullptr;

		textBox = nullptr;
		tileInfo = nullptr;

		canDrawMouseOnMap = false;

		buttons = nullptr;

		buttonPressed = -1;
		player = nullptr;
	}
	MainGame(Font*font)
	{
		world = new World({ 10,10 });
		unit = new Unit({ 10,10 });
		view = new View({ 800,450 }, { 1600, 900 });
		origin = view->getCenter();
		textBox = new TextBox( { view->getSize().x, (view->getSize().y * 0.2f) }, { 0,static_cast<float>(view->getSize().y * 0.8) }, font, L"AWd", Color(255, 0, 0, 255), Color(255, 0, 0, 255), Color(255, 0, 0, 255));
	
		worldArea.setSize({ static_cast<float>(view->getSize().x),static_cast<float>(view->getSize().y * 0.8) });
		//worldArea.setPosition(0, 0);
	
		mouseOnTileTexture.loadFromFile("Resources\\Textures\\ramka.png");
		mouseOnTile.setTexture(mouseOnTileTexture);

		//tile info
		tileInfo = new TextBox({ 100,50 }, { 0,0 }, font, L"Inormacje dotycz¹ce pola", Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0), 12);
		canDrawMouseOnMap = false;


		//Przyciski
		buttons = new Button({ view->getSize().x * 0.2f, (view->getSize().y * 0.18f) }, { 10,static_cast<float>(view->getSize().y * 0.82) }, font, L"AWd", Color(255, 200, 0, 255), Color(235, 0, 0, 255), Color(215, 0, 0, 255));
		buttonPressed = -1;





		player = new Player(world);
	
	}
	~MainGame()
	{
		delete textBox;
		delete tileInfo;
		delete view;
		delete world;
	}

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

		//Obs³uga przycisków gui
		UpdateButtons(window);
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
	World* world;
	Unit* unit;
	View*  view ;
	Vector2f offset;
	Vector2f origin;


	TextBox* textBox;


	Player* player;


	
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
	Button* buttons;
	unsigned short buttonPressed;


	void BuildBuilding(Vector2i _worldPos, short _type)
	{

	}


	void ChangeGuiPosition()
	{
		textBox->Move(offset);
		buttons->Move(offset);
	}
	
	void UpdateButtons(RenderWindow*window)
	{
		buttons->Update(static_cast<Vector2f>(Mouse::getPosition(*window)));
		if (buttons->GetButtonState() == PRESSED)
		{
			buttonPressed = 0;
			textBox->SetString(L"Wybierz pozycje");
		}

		
	}
	void RenderButtons(RenderTarget*target)
	{
		buttons->Render(target);
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
				if (buttonPressed == 0)
				{
					buttonPressed = -1;
					textBox->SetString(L"awdje");

					//BuildBuilding(mousePosOnMap, 0);
					world->SetBuilding(mousePosOnMap, 2);
				}
				else
				{
					buttonPressed = -1;
					
					
					textBox->SetString(L"Wybrane pole:\nx:" + to_wstring(mousePosOnMap.x)+" y:"+ to_wstring(mousePosOnMap.y));
				}
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
			tileInfo->SetString(tileInfoText);
	}
	void RenderTileInfo(RenderTarget* target)
	{
		if (canDrawMouseOnMap)
			tileInfo->Render(target);
	}
};
