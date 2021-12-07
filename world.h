#pragma once
enum
{//   0       1       2
	Zwykle, Drewno, Kamien
};

class World
{
public:
	World();
	~World();
	int type;


private:

};

World::World()
{
	type = 0;
}

World::~World()
{
}