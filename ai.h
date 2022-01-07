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

	void SetWorldSize(Vector2i _worldSize)
	{
		worldSize = _worldSize;
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
		if (startPos.x < 0)
			startPos.x = 0;
		if (startPos.x > worldSize.x-1)
			startPos.x = worldSize.x - 1;
		if (startPos.y < 0)
			startPos.y = 0;
		if (startPos.y > worldSize.y - 1)
			startPos.y = worldSize.y - 1;

		return startPos;
	}
private:
	int maxDistance;

	Vector2i startingBuildingPos;
	Vector2i worldSize;
};