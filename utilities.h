#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

/*Ten plik zawiera podstawowe enum'y i moze jakieœ statyczne funkcje globalne*/

enum GROUNDTYPES
{//   0       1       2
	NOTHING, GRASS, WOOD, STONE, IRON
};
enum GAMESTATE
{
	STARTMENU, LOGINMENU, REGISTEMENU, MAINMENU, GAME, NEWGAME, LOADGAME, EXITGAME
};

enum ButtonStates {
	IDLE, HOVER, PRESSED, ACTIVE
};

struct InGameResources
{
	int wood =0;
	int iron =0;
	int gold=0;
	int food =0;
};

InGameResources operator-(InGameResources a, InGameResources b)
{
	a.food -= b.food;
	a.iron  -= b.iron ;
	a.wood  -= b.wood ;
	a.gold  -= b.gold ;
	return a;
}
bool operator<=(InGameResources a, InGameResources b)
{
	if (a.food <= b.food && a.iron <= b.iron && a.gold <= b.gold && a.wood <= b.wood)
		return true;
	return false;
}

bool operator<(Vector2i a, Vector2i b)
{
	return a.x < b.x && a.y < b.y ? true : false;
}
bool operator<=(Vector2i a, Vector2i b)
{
	return a.x <= b.x&& a.y <= b.y ? true : false;
}
bool operator>=(Vector2i a, Vector2i b)
{
	return a.x >= b.x && a.y >= b.y ? true : false;
}
Vector2i operator+(Vector2i a, unsigned short b)
{
	return Vector2i(a.x + b, a.y + b);
}
Vector2i operator-(Vector2i a, unsigned short b)
{
	return Vector2i(a.x - b, a.y - b);
}

static Vector2i absVector2i(Vector2i a)
{
	return Vector2i(a.x < 0 ? a.x *= -1 : a.x, a.y < 0 ? a.y *= -1 : a.y);
}

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

void Delay(Int32 ms)
{
	Clock clock;
	clock.restart();

	while (clock.getElapsedTime().asMilliseconds() <= ms)
	{

	}
}