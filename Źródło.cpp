#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

//Huber -> jednostki
//Kacper -> world
//ja -> ?

int main()
{
	RenderWindow window(VideoMode(1600, 900, 64), "Gra IO");

	Event events;

	while (window.isOpen())
	{
		//Events
		while (window.pollEvent(events))
		{
			if (events.type == Event::Closed)
				window.close();
		}

		//obsluga klawiszy



		//obliczenia



		//rysowanie



	}

	return 0;
}