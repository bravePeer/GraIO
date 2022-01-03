#pragma once


class AI
{
public:
	AI()
	{
		srand(time(NULL));
		maxDistance = 3;
	//	startingBuildingPos = startingPos;
		cout << "AI zainicjowane";
	}
	void SetStartingPos(Vector2i startingPos)
	{
		startingBuildingPos = startingPos;
	}
	Vector2i GetStartingPos()
	{
		return startingBuildingPos;
	}
	short CalculateAction()
	{
		return rand() % 3;
	}
	Vector2i RandomPos(Vector2i startPos)
	{
		startPos.x += rand() % maxDistance * 2 + 1 - maxDistance;
		startPos.y += rand() % maxDistance * 2 + 1 - maxDistance;
		return startPos;
	}
private:
	int maxDistance;

	Vector2i startingBuildingPos;
};