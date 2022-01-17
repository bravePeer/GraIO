#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "gameStates.h"
#include "utilities.h"
#include "MainGame.h"

using namespace sf;

/*"Silnik" gry*/
class Game
{
public:
	Game()
	{
		window = new RenderWindow(VideoMode(1600, 900, 64), "Gra IO");
		font.loadFromFile("Resources\\Fonts\\comic.ttf");
		window->setVerticalSyncEnabled(true);
		window->setFramerateLimit(60);
		//startMenu = new StartMenu(&font);
		//mainMenu = new MainMenu(&font);

		gameMenuState = STARTMENU;
		events = new Event;

		gameState = new StartMenu(&font);
	}
	~Game()
	{
		//delete startMenu;
		delete gameState;
		delete events;
		delete window;
	}

	//Aktualizowanie
	void Update()
	{
		Time elapsed = clock.restart();
		
		PollEvents();

		gameState->Update(window, &elapsed);

		if (State* s = gameState->IsStateChanged())
		{
			delete gameState;
			gameState = s;
		}
	}

	//Rysowanie
	void Render()
	{
		window->clear();

		gameState->Render(window);

		window->display();
	}

	bool IsRunning()
	{
		return window->isOpen();
	}
private:
	void PollEvents()
	{
		while (window->pollEvent(*events))
		{
			switch (events->type)
			{
			case Event::Closed:
				window->close();
				break;
			case Event::KeyPressed:
				if (Keyboard::isKeyPressed(Keyboard::Escape))
					window->close();
				
					break;
			case Event::TextEntered:
				if (dynamic_cast<LoginMenu*>(gameState))
					dynamic_cast<LoginMenu*>(gameState)->AddLetter(events->text.unicode);
				else if(dynamic_cast<RegisterMenu*>(gameState))
					dynamic_cast<RegisterMenu*>(gameState)->AddLetter(events->text.unicode);
				break;
			}

		}
	}

	RenderWindow* window = nullptr;
	Event* events = nullptr;

	//Textury do menu

	Font font;
	//StartMenu* startMenu = nullptr;
	//MainMenu* mainMenu = nullptr;
	Clock clock;

	
	//Co ma byæ wyœwietlane w sensie ktore menu
	short gameMenuState;
	State* gameState = nullptr;
};