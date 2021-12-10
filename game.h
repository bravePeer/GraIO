#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "gui.h"
#include "utilities.h"

using namespace sf;

/* Stan gry -> jakie menu */


/*"Silnik" gry*/
class Game
{
public:
	Game()
	{
		window = new RenderWindow(VideoMode(1600, 900, 64), "Gra IO");
		font.loadFromFile("Resources\\Fonts\\comic.ttf");

		startMenu = new StartMenu(&font);
		mainMenu = new MainMenu(&font);

		gameMenuState = STARTMENU;
		events = new Event;
	}
	~Game()
	{
		delete startMenu;
		
		delete events;
		delete window;
	}

	//Aktualizowanie
	void Update()
	{
		PollEvents();
		
		//Wyswietlanie menu a bardziej aktualny status 
		switch (gameMenuState)
		{
		case STARTMENU:
			startMenu->Update(static_cast<Vector2f>(Mouse::getPosition(*window)));
				gameMenuState = startMenu->GetButtonPressed();
			break;
		case LOGINMENU:
			cout << "loginMenu" << endl;
			break;
		case REGISTEMENU:
			cout << "RegisteMenu" << endl;

			break;
		case MAINMENU:
			mainMenu->Update(static_cast<Vector2f>(Mouse::getPosition(*window)));
				gameMenuState = mainMenu->GetButtonPressed();
			break;


		case EXITGAME:
			window->close();
			return;
		}

		
	}

	//Rysowanie
	void Render()
	{
		window->clear();
		switch (gameMenuState)
		{
		case STARTMENU:
			startMenu->Render(window);
			break;
		case LOGINMENU:
			break;
		case REGISTEMENU:
			break;
		case MAINMENU:
			mainMenu->Render(window);
			break;
		}

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
				switch (gameMenuState)
				{
				case LOGINMENU:

					break;
				}
				//inputbox->AddLetter(events.text.unicode);
				break;
			}

		}
	}

	RenderWindow* window = nullptr;
	Event* events = nullptr;

	//Textury do menu

	Font font;
	StartMenu* startMenu = nullptr;
	MainMenu* mainMenu = nullptr;
	
	
	//Co ma byæ wyœwietlane w sensie ktore menu
	short gameMenuState;
};