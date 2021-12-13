#pragma once
#include <SFML/Graphics.hpp>
#include "unit.h"
#include "building.h"
#include "ai.h"
#include "world.h"
#include "gui.h"

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
	}
	MainGame(Font*font)
	{
		world = new World({ 10,10 });
		view = new View({ 800,450 }, { 1600, 900 });
		origin = view->getCenter();
		textBox = new TextBox( { view->getSize().x, (view->getSize().y * 0.2f) }, { 0,0 }, font, "Jakis teskst:", Color(255, 0, 0, 255), Color(255, 0, 0, 255), Color(255, 0, 0, 255));
	}
	~MainGame()
	{
		delete textBox;
		
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

		//Myszka


		

		
	}
	void Render(RenderTarget* target)
	{
		world->Render(target);
	
		textBox->Render(target);
	}
private:
	World* world;
	View*  view ;
	Vector2f offset;
	Vector2f origin;

	TextBox* textBox;
};
