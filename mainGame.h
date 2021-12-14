#pragma once
#include <SFML/Graphics.hpp>
#include "unit.h"
#include "building.h"
#include "ai.h"
#include "world.h"
#include "gui.h"
#include "user.h"

using namespace sf;

/*G³ówna gra*/
class MainGame : public State
{
public:
	MainGame()
	{
		world = nullptr;
		view = nullptr;

		textBox = nullptr;
		tileInfo = nullptr;

		canDrawMouseOnMap = false;
	}
	MainGame(Font*font)
	{
		world = new World({ 10,10 });
		view = new View({ 800,450 }, { 1600, 900 });
		origin = view->getCenter();
		textBox = new TextBox( { view->getSize().x, (view->getSize().y * 0.2f) }, { 0,static_cast<float>(view->getSize().y * 0.8) }, font, L"AWd", Color(255, 0, 0, 255), Color(255, 0, 0, 255), Color(255, 0, 0, 255));
	
		worldArea.setSize({ static_cast<float>(view->getSize().x),static_cast<float>(view->getSize().y * 0.8) });
		//worldArea.setPosition(0, 0);
	
		mouseOnTileTexture.loadFromFile("Resources\\Textures\\obram.png");
		mouseOnTile.setTexture(mouseOnTileTexture);

		//tile info
		tileInfo = new TextBox({ 100,50 }, { 0,0 }, font, L"Inormacje dotycz¹ce pola", Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0), 12);
		canDrawMouseOnMap = false;
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
			
			offset.x = 1 * elapsed->asMilliseconds();
			origin.x -= offset.x;
			view->setCenter(origin);
			window->setView(*view);


			//Ustawianie pozycji
			textBox->SetPostition({ textBox->GetPosition().x - offset.x ,textBox->GetPosition().y });
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			offset.x = 1 * elapsed->asMilliseconds();
			origin.x += offset.x;
			view->setCenter(origin);
			window->setView(*view);

			//Ustawianie pozycji
			textBox->SetPostition({ textBox->GetPosition().x + offset.x ,textBox->GetPosition().y });
		}
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			offset.y = 1 * elapsed->asMilliseconds();
			origin.y -= offset.y;
			view->setCenter(origin);
			window->setView(*view);

			//Ustawianie pozycji
			textBox->SetPostition({ textBox->GetPosition().x, textBox->GetPosition().y - offset.y  });
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			offset.y = 1 * elapsed->asMilliseconds();
			origin.y += offset.y;
			view->setCenter(origin);
			window->setView(*view);

			//Ustawianie pozycji
			textBox->SetPostition({ textBox->GetPosition().x, textBox->GetPosition().y + offset.y  });
		}

		//Os³uga myszki
		MouseOnWorld(window);
		
		UpdateTileInfo(window);
		
	}
	void Render(RenderTarget* target)
	{
		/*Œwiat*/
		world->Render(target);
	

		/*Klikniête elementy*/
		RenderMouse(target);



		/*Pzyciski i faktyczne gui xd*/
		textBox->Render(target);

		RenderTileInfo(target);
	}
private:
	World* world;
	View*  view ;
	Vector2f offset;
	Vector2f origin;


	TextBox* textBox;

	
	/* do myszki */
	RectangleShape worldArea;
	bool canDrawMouseOnMap;
	Texture mouseOnTileTexture;
	Sprite mouseOnTile;
	Vector2i mousePosOnMap;


	/* informacje o tile */
	TextBox* tileInfo;


	void MouseOnWorld(RenderWindow*window)
	{
		Vector2i mousePos = Mouse::getPosition(*window);
		canDrawMouseOnMap = false;

		if (worldArea.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
		{
			Vector2i pos = Vector2i(mousePos.x % window->getSize().x, mousePos.y % window->getSize().y) - Vector2i(window->getSize().x / 2, window->getSize().y / 2);
			mousePosOnMap = Screen2Map(static_cast<Vector2i>(Vector2f(pos.x , pos.y )) + static_cast<Vector2i>(window->getView().getCenter()), { TILEW,TILEH });
			

			canDrawMouseOnMap = true;
			mouseOnTile.setPosition(ScreenPos(mousePosOnMap, { TILEW,TILEH }));
		}
	}
	void RenderMouse(RenderTarget* target)
	{
		if (canDrawMouseOnMap)
			target->draw(mouseOnTile);
	}
	void UpdateTileInfo(RenderWindow* window)
	{
		tileInfo->SetPostition({ static_cast<float>(Mouse::getPosition(*window).x) + 20 - offset.x,static_cast<float>(Mouse::getPosition(*window).y - offset.y) });
		String tileInfoText = L"Zawartoœæ pola:\n";
		Tile tile = world->GetTile(mousePosOnMap);
		
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
