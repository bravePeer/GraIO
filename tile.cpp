#include "tile.h"

Tile::Tile(std::string textureName, float x, float y, bool empty)
{
	if (!setUpSprite(textureName))
	{
		return;
	}
	pos = sf::Vector2f(x, y);
	sprite.setPosition(pos);
	isEmpty = empty;
}

bool Tile::setUpSprite(std::string textureName)
{
	if (!texture.loadFromFile("textures/groundBlock.png"))
	{
		return 0;
	}
	texture.setSmooth(true);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
	return true;
}