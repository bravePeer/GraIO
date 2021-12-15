#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

/*Ten plik zawiera podstawowe enum'y i moze jakieœ statyczne funkcje globalne*/

enum GAMESTATE
{
	STARTMENU, LOGINMENU, REGISTEMENU, MAINMENU, GAME, NEWGAME, LOADGAME, EXITGAME
};

enum ButtonStates {
	IDLE, HOVER, PRESSED, ACTIVE
};

static Vector2f ScreenPos(Vector2i map, Vector2i tileSize)
{
	return Vector2f(static_cast<float>((map.x - map.y) * (tileSize.x / 2)), static_cast<float>((map.x + map.y) * (tileSize.y / 2)));
}

static Vector2i Screen2Map(Vector2i screen, Vector2i tileSize)
{
	Vector2i map((screen.y / tileSize.y - 0) + (screen.x / tileSize.x - 0), (screen.y / tileSize.y - 0) - (screen.x / tileSize.x - 0));

	if (screen.y % tileSize.y < (screen.x % tileSize.x) / (-2) + 64)
		map.x--;
	if (screen.y % tileSize.y < (screen.x % tileSize.x) / (2) - 64)
		map.y--;
	if (screen.y % tileSize.y > (screen.x % tileSize.x) / (2) + 64)
		map.y++;
	if (screen.y % tileSize.y > (screen.x % tileSize.x) / (-2) + 192)
		map.x++;

	return map;
}