#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Building
{
public:
	Building(String _name, String _desc, Sprite *_sprite)
		:name(_name), desc(_desc), sprite(_sprite)
	{

	}
	~Building()
	{
	}

	virtual void Render(RenderTarget* target)
	{

	}
private:
	String name;
	String desc;
	Sprite* sprite;
};