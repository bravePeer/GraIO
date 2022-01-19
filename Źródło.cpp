#include <iostream>
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
	
	return 0;
}