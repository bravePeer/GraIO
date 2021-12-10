//#include <iostream>
//#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
#include "game.h"
#include <Windows.h>

//Huber -> jednostki
//Kacper -> world
//ja -> wszytko i nic xd

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

	return 0;
}