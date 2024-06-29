#pragma once
#include "Player.h"
#include "ConsoleHelper.h"

class MapManager
{
public:
	MapManager();

	void CheckCollisionsAndMove(Player* player, int x, int y);
	void RenderLevel(Player player);

private:
	ConsoleHelper* cHelper;

	char GetNextPosition(int posX, int posY, int movementX, int movementY);
	void CreateRoom(int height, int width);
	void RenderElement(int x, int y, char element);
};

