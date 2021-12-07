#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1600, 900, 64), "Gra IO");

	Event events;

	while (window.isOpen())
	{
		while (window.pollEvent(events))
		{
			if (events.type == Event::Closed)
				window.close();
		}


	}

	return 0;
}