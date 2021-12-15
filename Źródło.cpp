#include <iostream>
//#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
#include "game.h"
#include <Windows.h>
#include "world.h"

//Huber -> jednostki/ budynki
//Kacper -> grafiki
//ja -> wszystko

int main()
{
	
	Game game;
	//ShowWindow(GetConsoleWindow(), SW_HIDE);	//Znika konsole
	//ShowWindow(GetConsoleWindow(), SW_RESTORE);	//Odznika konsole

	while (game.IsRunning())
	{
		//update
		game.Update();

		//rysowanie
		game.Render();
	}
	

	/*
	sf::RenderWindow window(sf::VideoMode(400, 400), "Gra");
	World nworld = World();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear();
		
		for (int i = 0; i < nworld.gridLenght; i++)
		{
			for (int j = 0; j < nworld.gridLenght; j++)
			{
				window.draw(nworld.tiles[i][j]->sprite);
			}
		}
		
		
		window.display();
		
	}
	*/
	return 0;
}